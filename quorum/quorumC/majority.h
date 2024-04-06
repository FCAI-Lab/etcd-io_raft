#ifndef MAJORITY_H_
#define MAJORITY_H_

#include "quorum.h"
#include "vector.h"
#include <stdbool.h>
#include <string.h>

typedef struct MajorityConfig_content {
  uint64_t id;
} MajorityConfig_content;

typedef struct MajorityConfig {
  vector v;
} MajorityConfig;

// sort slice by ascending & slice -> string
const char *cMajorityConfig(void *p, int size);

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void *p, int size);

void cinsertionSort(void *p, int size);

Index CommittedIndex(MajorityConfig, mapAckIndexer);

typedef struct {
  uint64_t id;
  Index idx;
  bool ok;
  int bar;
} tup;

char *DescribeC(int c_len, void *c_range, void *l_range_idx, void *l_range_ok);

int compare_by_index(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);
int compare(const void *a, const void *b);

#endif