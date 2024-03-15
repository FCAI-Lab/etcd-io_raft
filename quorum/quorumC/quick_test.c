#include "quick_test.h"

Index alternativeMajorityCommittedIndex(MajorityConfig c, mapAckIndexer l) {
    size_t lenC = vector_total(&c.v);
    if (lenC == 0) {
        return UINT64_MAX;
    }

    // idToIdx is map and has id, idx
    vector idToIdx;
    vector_init(&idToIdx, sizeof(mapAckIndexer_content));

    for(int j = 0; j < lenC; j++){
		MajorityConfig_content MajorityConfig = *(MajorityConfig_content*) vector_get(&c.v, j);
		uint64_t id = MajorityConfig.id;
        Index* idx = AckedIndex(&l, id);
		if(idx != NULL) {
            mapAckIndexer_content m;
            m.id = id;
            m.idx = *idx;
            vector_add(&idToIdx, &m);
		}
	}

    // Q&A : Talking about idxToVotes Type
    vector idxToVotes;
    vector_init(&idxToVotes, sizeof(mapAckIndexer_content));

    // Add
    lenC = vector_total(&idToIdx);

    for (int i = 0; i < lenC; i++) {
        Index idx = (*(mapAckIndexer_content*)vector_get(&idToIdx, i)).idx;
        mapAckIndexer_content m;
        m.id = idx;
        m.idx = 0;
        vector_add(&idxToVotes, &m);
    }

    for (int i = 0; i < lenC; i++) {
        for (int j = 0; j < lenC; j++) {  // Iterate from current index to higher indexes
            mapAckIndexer_content idy = *(mapAckIndexer_content*)vector_get(&idxToVotes, j);
            Index idx = (*(mapAckIndexer_content*)vector_get(&idToIdx, i)).idx;
            if(idy.id > idx){
                continue;
            }
            idy.idx++;
            vector_set(&idxToVotes, j, &idy);
        }
    }

    int q = vector_total(&c.v) / 2 + 1;
    uint64_t maxQuorumIdx = 0;

    for (int i = 0; i < lenC; i++) {
        mapAckIndexer_content m = *(mapAckIndexer_content*)vector_get(&idxToVotes, i);
        uint64_t idx = m.id;
        uint64_t n = m.idx;

        if (n >= q && idx > maxQuorumIdx) {
            maxQuorumIdx = idx;
        }
    }

    // Free allocated memory
    vector_free(&idToIdx);
    vector_free(&idxToVotes);

    return maxQuorumIdx;
}