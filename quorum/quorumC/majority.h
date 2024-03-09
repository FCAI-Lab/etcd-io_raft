//quorum.h
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vector.h"

typedef struct MajorityConfig_content{
    uint64_t id;
} MajorityConfig_content;

typedef struct MajorityConfig {
    vector v;
} MajorityConfig;

int compare(const void *a, const void *b);

// sort slice by ascending & slice -> string
const char* cMajorityConfig(void* p, int size);

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void* p, int size);

void cinsertionSort(void* p, int size);