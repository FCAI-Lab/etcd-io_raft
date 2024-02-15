//quorum.h
#ifndef _MAJORITY_H
#define _MAJORITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int compare(const void *a, const void *b);

// sort slice by ascending & slice -> string
const char* cMajorityConfig(void* p, int size);

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void* p, int size);

void cinsertionSort(void* p, int size);

#endif