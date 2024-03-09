#include "bench_test.h"
#include "vector.h"
#include "majority.h"
#include "quorum.h"
#include <stdio.h>
#include <limits.h>

MajorityConfig c;
mapAckIndexer l;

void cBenchmarkMajorityConfig_CommittedIndex(int b_N, int n) {
    
    vector_init(&c.v, sizeof(MajorityConfig_content));
    vector_init(&l.v, sizeof(mapAckIndexer_content));

    // 고정으로 랜덤을 할 것.
    srand(2024);

    // 질문 : for문안에 INT64_MAX는 어떻게 처리?
    for(uint64_t i = 0; i < n; i++) {
        MajorityConfig_content _majorityConfig_content;
        mapAckIndexer_content _mapAckIndexer_content;
        _majorityConfig_content.id = i + 1;
        _mapAckIndexer_content.id = i + 1;
        _mapAckIndexer_content.idx = rand() % (INT64_MAX);
        vector_add(&c.v, &_majorityConfig_content);
        vector_add(&l.v, &_mapAckIndexer_content);
    }
}

uint64_t majorityConfigId(size_t index) {
    MajorityConfig_content _majorityConfigId = *(MajorityConfig_content*)vector_get(&c.v, index);
    return _majorityConfigId.id;
}

uint64_t mapAckIndexerId(size_t index) {
    mapAckIndexer_content _mapAckIndexer_content = *(mapAckIndexer_content*)vector_get(&c.v, index);
    return _mapAckIndexer_content.id;
}

uint64_t mapAckIndexerIdx(size_t index) {
    mapAckIndexer_content _mapAckIndexer_content = *(mapAckIndexer_content*)vector_get(&c.v, index);
    return _mapAckIndexer_content.idx;
}

void majorityConfigmapAckIndexerFree() {
    vector_free(&c.v);
    vector_free(&l.v);  
}