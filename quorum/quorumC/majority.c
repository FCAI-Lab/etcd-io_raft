#include "majority.h"

char *DescribeC(int c_len, void *c_range, void *l_range_idx, void *l_range_ok) {
  if (c_len == 0) {
    return "<empty majority quorum>";
  }

  // Below, populate .bar so that the i-th largest commit index has bar i (we
  // plot this as sort of a progress bar). The actual code is a bit more
  // complicated and also makes sure that equal index => equal bar.

  int n = c_len;
  tup *info = malloc(n * sizeof(tup));
  uint64_t *ids = (uint64_t *)c_range;
  uint64_t *idxs = (uint64_t *)l_range_idx;
  bool *oks = (bool *)l_range_ok;
  for (int i = 0; i < n; ++i) {
    // 원본에서 MajorityConfig은 map이므로 key를 순회합니다.
    uint64_t id = ids[i];
    uint64_t idx = idxs[i];
    bool ok = oks[i];

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

  char *buf = malloc(1024);
  buf[0] = '\0';

  // Print.
  char *line = malloc(1024);
  sprintf(line, "%*s    idx\n", n, " ");
  strncat(buf, line, 1024);

  for (int i = 0; i < n; ++i) {
    // 원본에서 info는 slice이므로 index를 순회합니다.
    int bar = info[i].bar;
    if (!info[i].ok) {
      sprintf(line, "?%*s", n, " ");
    } else {
      char repeat[bar + 1];
      memset(repeat, 'x', bar);
      repeat[bar] = '\0';
      sprintf(line, "%s>%*s", repeat, n - bar, " ");
    }
    strncat(buf, line, 1024);

    sprintf(line, " %5llu    (id=%llu)\n", info[i].idx, info[i].id);
    strncat(buf, line, 1024);
  }

  free(line);
  free(info);

  return buf;
}

int compare_by_index(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  if (a_comp.idx == b_comp.idx) {
    return a_comp.id < b_comp.id ? -1 : 1;
  } else {
    return a_comp.idx < b_comp.idx ? -1 : 1;
  }
}

int compare_by_id(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  return a_comp.id < b_comp.id ? -1 : 1;
}