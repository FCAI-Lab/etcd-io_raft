#pragma once
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "vector.h"
#include "majority.h"

void cBenchmarkMajorityConfig_CommittedIndex(int b_N, int n);

uint64_t majorityConfigId(size_t index);

uint64_t mapAckIndexerId(size_t index);

uint64_t mapAckIndexerIdx(size_t index);

void majorityConfigmapAckIndexerFree();