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
	uint64_t* sl = (uint64_t*) p;
    int a = 0, b = size;
    for (int i = a + 1; i < b; i++) {
		for (int j = i; j > a && sl[j] < sl[j-1]; j--) {
			uint64_t tmp = sl[j];
			sl[j] = sl[j-1];
			sl[j-1] = tmp;
		}
	}
}

Index CommittedIndex(MajorityConfig c, mapAckIndexer l) {
	size_t n = vector_total(&c.v);
	if (n == 0) {
		return UINT64_MAX;
	}

	uint64_t* srt = (uint64_t*)calloc(n, sizeof(uint64_t));
	for(size_t i = 0; i < n; i++){
		srt[i] = 0;
	}

	size_t i = n - 1;
	for(int j = 0; j < n; j++){
		MajorityConfig_content* MajorityConfig = (MajorityConfig_content*) vector_get(&c.v, j);
		Index* idx = AckedIndex(&l, (*MajorityConfig).id);
		if(idx != NULL) {
			srt[i] = *idx;
			i--;
		}
	}

	cinsertionSort(srt, n);

	uint64_t pos = n - (n/2 + 1);
	return (Index)srt[pos];
}