#ifndef ARRAYLIST_H
#define ARRAYLIST_H

// This is macro magic to make generic types in c. Dont question it.
// Dont look too into it. May not be completely safe. But it tickels
// my brain.

#define init(_plist) \
    _plist->functions->init()

#define DEFINE_ARRAY_LIST(_T)                                                                       \
    typedef struct {                                                                                \
        void (*init)(struct arraylist_##_T*);                                                       \
        void (*append)(struct arraylist_##_T*, _T);                                                 \
        _T (*pop)(struct arraylist_##_T*);                                                          \
        void (*deinit)(struct arraylist_##_T*);                                                     \
    } fp_##_T;                                                                                      \
    typedef struct arraylist_##_T{                                                                  \
      _T* items;                                                                                    \
      size_t len, capacity;                                                                         \
      fp_##_T functions;                                                                            \
    }arraylist_##_T##_t;                                                                            \
                                                                                                    \
    static inline                                                                                   \
    void arraylist_##_T##_init(arraylist_##_T##_t *list) {                                          \
      list->items = malloc(sizeof(_T));                                                             \
      list->len = 0;                                                                                \
      list->capacity = 1;                                                                           \
    }                                                                                               \
                                                                                                    \
    static inline                                                                                   \
    void arraylist_##_T##_push(arraylist_##_T##_t *list, _T item) {                                 \
      if (list->len + sizeof(item) > list->capacity) {                                              \
          size_t old_cap = list->capacity;                                                          \
          size_t new_cap = old_cap*2;                                                               \
          size_t new_size = list->len + sizeof(item);                                               \
          list->items = realloc(list->items, new_size);                                             \
          list->capacity = new_cap;                                                                 \
      }                                                                                             \
      list->items[list->len + 1] = item;                                                            \
    }                                                                                               \

#endif
