#ifndef _MAJORITY_H
#define _MAJORITY_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../_obj/_cgo_export.h"
#include "../quorumC/quorum.h"

typedef struct {
  uint64_t id;
  Index idx;
  bool ok;
  int bar;
} tup;

char *DescribeC(int c_len, void *c_range, void *l);

int compare_by_index(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);

#endif