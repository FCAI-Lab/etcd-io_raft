#ifndef _QUORUM_H
#define _QUORUM_H

#include "../majorityC/vector.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t Index;

const char *index_to_string(uint64_t i);

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