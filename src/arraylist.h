#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "alloc.h"

#define DEFINE_ARRAY_LIST(_T)                     \
  typedef struct {                                \
    _T* data;                                     \
    size_t size, capacity;                        \
    allocator_t *allocator;                       \
  }arraylist_##_T##_t;                            \

#endif
