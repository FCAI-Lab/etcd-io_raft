#include "majority.h"

char *DescribeC(void *c, void *l) {
  if (MajorityConfigLength(c) == 0) { // Admmited
    return "<empty majority quorum>";
  }
  typedef struct {
    uint64_t id;
    Index idx;
    bool ok;
    int bar;
  } tup;

  int n = MajorityConfigLength(c); // Admmited
  tup *info = malloc(n * sizeof(tup));
  for (int i = 0; i < n; ++i) {
    // TODO: AckedIndex
  }

  // Sort by index
  // TODO: Sort

  // Populate .bar.
  for (int i = 0; i < n; ++i) {
    if (i > 0 && info[i - 1].idx < info[i].idx) {
      info[i].bar = i;
    }
  }

  // Sort by ID.
  // TODO: Sort

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
    sprintf(buf, " %5d    (id=%d)\n", info[i].idx, info[i].id);
  }
  return buf;
}