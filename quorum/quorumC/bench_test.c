#include "bench_test.h"

MajorityConfig c;
mapAckIndexer l;

void cBenchmarkMajorityConfig_CommittedIndex(int b_N, int n) {
  vector_init(&c.v, sizeof(MajorityConfig_content));
  vector_init(&l.v, sizeof(mapAckIndexer_content));

  srand(2024);

  for (uint64_t i = 0; i < n; i++) {
    MajorityConfig_content _majorityConfig_content;
    mapAckIndexer_content _mapAckIndexer_content;
    _majorityConfig_content.id = i + 1;
    _mapAckIndexer_content.id = i + 1;
    _mapAckIndexer_content.idx = rand() % (INT64_MAX);
    vector_add(&c.v, &_majorityConfig_content);
    vector_add(&l.v, &_mapAckIndexer_content);
  }

  for (int i = 0; i < b_N; i++) {
    cCommittedIndex(c, l);
  }

  vector_free(&c.v);
  vector_free(&l.v);
}