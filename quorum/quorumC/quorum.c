#include "quorum.h"

const char *index_to_string(uint64_t i) {
    static char buffer[21]; // buffer size for uint64_t
    if (i == UINT64_MAX) {
        return "∞";
    }
    snprintf(buffer, sizeof(buffer), "%" PRIu64, (uint64_t)i);
    return buffer;
}

Index* AckedIndex(void* test, uint64_t id) {
    mapAckIndexer*m = (mapAckIndexer*)test;
    Index* idx = NULL;
    
    for(int i = 0; i < vector_total(&m->v); i++){
        mapAckIndexer_content mapAckIndexer_tmp = *(mapAckIndexer_content*) vector_get(&m->v, i);
        if (mapAckIndexer_tmp.id == id) {
            idx = &mapAckIndexer_tmp.idx;    // id값이 없으면 ERROR! => pointer는 어떠할까요? 없으면 NULL을 return
        }
    }

    return idx;
}