#include "majority.h"

char *DescribeC(void *c, void *l) {
  if (MajorityConfigLength(c) == 0) { // Admmited
    return "<empty majority quorum>";
  }

  int n = MajorityConfigLength(c); // Admmited
  tup *info = malloc(n * sizeof(tup));
  uint64_t *ids = MajorityConfigRange(c); // Admmited
  for (int i = 0; i < n; ++i) {
    uint64_t id = ids[i];
    uint64_t idx;
    void *ok;
    AckedIndexC(l, id, &idx, &ok); // Admmited
    info[i] = (tup){id, idx, *(bool *)ok, 0};
  }

  // Sort by index
  qsort(info, n, sizeof(tup), compare_by_index);

  // Populate .bar.
  for (int i = 0; i < n; ++i) {
    if (i > 0 && info[i - 1].idx < info[i].idx) {
      info[i].bar = i;
    }
  }

  // Sort by ID.
  qsort(info, n, sizeof(tup), compare_by_id);

  char *buf;
  buf = malloc(1000);

  // Print.
  sprintf(buf, "%*s    idx\n", n, " ");
  for (int i = 0; i < n; ++i) {
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