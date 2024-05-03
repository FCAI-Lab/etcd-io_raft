#ifndef QUORUM_H_
#define QUORUM_H_

#include "vector.h"
#include <inttypes.h>
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

// VoteResult indicates the outcome of a vote.
//
typedef uint8_t VoteResult;

enum {
  // VotePending indicates that the decision of the vote depends on future
  // votes, i.e. neither "yes" or "no" has reached quorum yet.
  VotePending = 1,
  // VoteLost indicates that the quorum has voted "no".
  VoteLost,
  // VoteWon indicates that the quorum has voted "yes".
  VoteWon
};

#endif