#ifndef _QUORUM_H
#define _QUORUM_H

#include "vector.h"
#include <inttypes.h>
#include <stdint.h>

typedef uint64_t Index;

// add id
typedef struct mapAckIndexer_content {
  uint64_t id;
  Index idx;
} mapAckIndexer_content;

typedef struct mapAckIndexer {
  vector v;
} mapAckIndexer;

Index *AckedIndex(void *, uint64_t);

#endif