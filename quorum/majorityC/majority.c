#include "majority.h"

// l 대신 미리 구현된 AckedIndexC를 사용해야 합니다.
char *DescribeC(int c_len, uint64_t *c_range, void *l) {
  if (c_len == 0) {
    return "<empty majority quorum>";
  }

  // Below, populate .bar so that the i-th largest commit index has bar i (we
  // plot this as sort of a progress bar). The actual code is a bit more
  // complicated and also makes sure that equal index => equal bar.

  int n = c_len;
  tup *info = malloc(n * sizeof(tup));
  uint64_t *ids = c_range;
  for (int i = 0; i < n; ++i) {
    // 원본에서 MajorityConfig은 map이므로 key를 순회합니다.
    uint64_t id = ids[i];

    uint64_t idx;
    bool ok;
    AckedIndexC(l, id, &idx, &ok); // Admmited

    info[i] = (tup){id, idx, ok, 0};
  }

  // Sort by index
  qsort(info, n, sizeof(tup), compare_by_index);

  // Populate .bar.
  for (int i = 0; i < n; ++i) {
    // 원본에서 info는 slice이므로 index를 순회합니다.
    if (i > 0 && info[i - 1].idx < info[i].idx) {
      info[i].bar = i;
    }
  }

  // Sort by ID.
  qsort(info, n, sizeof(tup), compare_by_id);

  char *buf;
  buf = malloc(1000); // 좀 더 최적의 Size로 할당해야 합니다.

  // Print.
  // 안정성을 위해 snprintf를 사용해야 합니다.
  sprintf(buf, "%*s    idx\n", n, " ");
  for (int i = 0; i < n; ++i) {
    // 원본에서 info는 slice이므로 index를 순회합니다.
    int bar = info[i].bar;
    if (!info[i].ok) {
      sprintf(buf, "?%*s", n, " ");
    } else {
      sprintf(buf, "%*s>%*s", bar, "x", n - bar, " ");
    }
    sprintf(buf, " %5" PRIu64 "    (id=%" PRIu64 ")\n", info[i].idx,
            info[i].id);
  }
  return buf;
}

int compare_by_index(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  if (a_comp.idx == b_comp.idx) {
    return a_comp.id < b_comp.id;
  }
  return a_comp.idx < b_comp.idx;
}

int compare_by_id(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  return a_comp.id < b_comp.id;
}