#include "quorum.h"

Index *AckedIndex(void *m, uint64_t id) {
  mapAckIndexer _m = *(mapAckIndexer *)m;
  Index *idx = NULL;

  for (size_t i = 0; i < vector_total(&_m.v); i++) {
    mapAckIndexer_content mapAckIndexer_tmp =
        *(mapAckIndexer_content *)vector_get(&_m.v, i);
    if (mapAckIndexer_tmp.id == id) {
      idx = &mapAckIndexer_tmp.idx; // id값이 없으면 ERROR! => pointer는
                                    // 어떠할까요? 없으면 NULL을 return
      break;
    }
  }

  return idx;
}