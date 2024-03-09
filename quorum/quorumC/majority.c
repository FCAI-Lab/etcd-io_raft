#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "majority.h"

int compare(const void *a, const void *b){
	return(*(long long unsigned int*)a - *(long long unsigned int*)b);
}

// sort slice by ascending & slice -> string
const char* cMajorityConfig(void* p, int size) {
	long long unsigned int* sl = (long long unsigned int*) p;

	qsort(sl, size, sizeof(long long unsigned int), compare);

	char* buf = (char*)malloc((2 * size + 3) * sizeof(char));

	int index = 0;
    buf[index++] = '(';
    for (int i = 0; i < size; i++) {
		if (i > 0) {
            buf[index++] = ' ';
        }
        index += sprintf(buf + index, "%llu", sl[i]);
    }
    buf[index++] = ')';
    buf[index] = '\0';

    return buf;
}

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void* p, int size) {
	// 형변환
    long long unsigned int* arr = (long long unsigned int*)p;
	qsort(arr, size, sizeof(long long unsigned int), compare);
}

void cinsertionSort(void* p, int size) {
	long long unsigned int* sl = (long long unsigned int*) p;
    int a = 0, b = size;
    for (int i = a + 1; i < b; i++) {
		for (int j = i; j > a && sl[j] < sl[j-1]; j--) {
			long long unsigned int tmp = sl[j];
			sl[j] = sl[j-1];
			sl[j-1] = tmp;
		}
	}
}