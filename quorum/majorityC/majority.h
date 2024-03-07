#ifndef _MAJORITY_H
#define _MAJORITY_H

#include <stdbool.h>
#include <stdlib.h>

#include "../quorumC/quorum.h"

typedef struct {
  uint64_t id;
  Index idx;
  bool ok;
  int bar;
} tup;

char *DescribeC(void *c, void *l);

int compare_by_index(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);

#endif