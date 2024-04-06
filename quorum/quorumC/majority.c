#include "majority.h"

// sort slice by ascending & slice -> string
const char *cMajorityConfig(void *p, int size) {
  long long unsigned int *sl = (long long unsigned int *)p;

  qsort(sl, size, sizeof(long long unsigned int), compare);

  char *buf = (char *)malloc((2 * size + 3) * sizeof(char));

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

char *cDescribe(int c_len, void *c_range, void *l_range_idx, void *l_range_ok) {
  if (c_len == 0) {
    return "<empty majority quorum>";
  }

  // Below, populate .bar so that the i-th largest commit index has bar i (we
  // plot this as sort of a progress bar). The actual code is a bit more
  // complicated and also makes sure that equal index => equal bar.

  int n = c_len;
  tup *info = malloc(n * sizeof(tup));
  uint64_t *ids = (uint64_t *)c_range;
  uint64_t *idxs = (uint64_t *)l_range_idx;
  bool *oks = (bool *)l_range_ok;
  for (int i = 0; i < n; ++i) {
    // 원본에서 MajorityConfig은 map이므로 key를 순회
    uint64_t id = ids[i];
    uint64_t idx = idxs[i];
    bool ok = oks[i];

    info[i] = (tup){id, idx, ok, 0};
  }

  // Sort by index
  qsort(info, n, sizeof(tup), compare_by_index);

  // Populate .bar.
  for (int i = 0; i < n; ++i) {
    // 원본에서 info는 slice이므로 index를 순회
    if (i > 0 && info[i - 1].idx < info[i].idx) {
      info[i].bar = i;
    }
  }

  // Sort by ID.
  qsort(info, n, sizeof(tup), compare_by_id);

  char *buf = malloc(1024);
  buf[0] = '\0';

  // Print.
  char *line = malloc(1024);
  snprintf(line, 1024, "%*s    idx\n", n, " ");
  strncat(buf, line, 1024);

  for (int i = 0; i < n; ++i) {
    // 원본에서 info는 slice이므로 index를 순회
    int bar = info[i].bar;
    if (!info[i].ok) {
      snprintf(line, 1024, "?%*s", n, " ");
    } else {
      char repeat[bar + 1];
      memset(repeat, 'x', bar);
      repeat[bar] = '\0';
      snprintf(line, 1024, "%s>%*s", repeat, n - bar, " ");
    }
    strncat(buf, line, 1024);

    snprintf(line, 1024, " %5" PRIu64 "    (id=%" PRIu64 ")\n", info[i].idx,
             info[i].id);
    strncat(buf, line, 1024);
  }

  free(line);
  free(info);

  return buf;
}

// sort.Slice(sl, func(i, j int) bool { return sl[i] < sl[j] }) 의 역활
void cSlice(void *p, int size) {
  // 형변환
  long long unsigned int *arr = (long long unsigned int *)p;
  qsort(arr, size, sizeof(long long unsigned int), compare);
}

void cinsertionSort(void *p, int size) {
  uint64_t *sl = (uint64_t *)p;
  int a = 0, b = size;
  for (int i = a + 1; i < b; i++) {
    for (int j = i; j > a && sl[j] < sl[j - 1]; j--) {
      uint64_t tmp = sl[j];
      sl[j] = sl[j - 1];
      sl[j - 1] = tmp;
    }
  }
}

Index cCommittedIndex(MajorityConfig c, mapAckIndexer l) {
  size_t n = vector_total(&c.v);
  if (n == 0) {
    return UINT64_MAX;
  }

  uint64_t *srt = (uint64_t *)calloc(n, sizeof(uint64_t));
  for (size_t i = 0; i < n; i++) {
    srt[i] = 0;
  }

  size_t i = n - 1;
  for (int j = 0; j < n; j++) {
    MajorityConfig_content *MajorityConfig =
        (MajorityConfig_content *)vector_get(&c.v, j);
    Index *idx = AckedIndex(&l, (*MajorityConfig).id);
    if (idx != NULL) {
      srt[i] = *idx;
      i--;
    }
  }

  cinsertionSort(srt, n);

  uint64_t pos = n - (n / 2 + 1);
  return (Index)srt[pos];
}

int compare_by_index(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  if (a_comp.idx == b_comp.idx) {
    return a_comp.id - b_comp.id;
  } else {
    return a_comp.idx - b_comp.idx;
  }
}

int compare_by_id(const void *a, const void *b) {
  tup a_comp = *(tup *)a;
  tup b_comp = *(tup *)b;

  return a_comp.id - b_comp.id;
}

int compare(const void *a, const void *b) {
  return (*(long long unsigned int *)a - *(long long unsigned int *)b);
}