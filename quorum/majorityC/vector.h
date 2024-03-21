#ifndef _VECTOR_H
#define _VECTOR_H
// vector 참고자료
// https://www.sanfoundry.com/c-program-implement-vector/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VECTOR_INIT_CAPACITY 4

typedef struct vector {
  void *items;
  size_t item_size;
  size_t capacity;
  size_t total;
} vector;

void vector_init(vector *, size_t item_size); // get vector then return vector
size_t vector_total(vector *);
static void vector_resize(vector *, size_t);
void vector_add(vector *, void *);
void vector_set(vector *, size_t, void *);
void *vector_get(vector *, size_t);
void vector_delete(vector *, size_t);
void vector_free(vector *);

#endif