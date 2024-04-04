#ifndef _MAJORITY_H
#define _MAJORITY_H

#include <stdbool.h>
#include <string.h>

#include "quorum.h"

typedef struct {
  uint64_t id;
  Index idx;
  bool ok;
  int bar;
} tup;

char *DescribeC(int c_len, void *c_range, void *l_range_idx, void *l_range_ok);

int compare_by_index(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);

#endif