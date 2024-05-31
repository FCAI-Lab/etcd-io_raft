#ifndef MAJORITY_H_
#define MAJORITY_H_

#include "quorum.h"
#include "vector.h"
#include <stdbool.h>

typedef struct MajorityConfig_content {
  uint64_t id;
} MajorityConfig_content;

typedef struct MajorityConfig {
  vector v;
} MajorityConfig;

typedef struct tup {
  uint64_t id;
  Index idx;
  bool ok;
  int bar;
} tup;

typedef struct VoteEntry {
  uint64_t v;
  bool ok;
} VoteEntry;

// sort slice by ascending & slice -> string
const char *cMajorityConfig(void *p, int size);

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void *p, int size);

char *cDescribe(int c_len, void *c_range, void *l_range_idx, void *l_range_ok);

void cinsertionSort(void *p, int size);

Index cCommittedIndex(MajorityConfig, mapAckIndexer);

VoteResult cVoteResult(VoteEntry *votes, int c_size);

int compare_by_index(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);
int compare(const void *a, const void *b);

#endif