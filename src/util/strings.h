#pragma once

#include "../forward.h"
#include "alloc.h"
#include <string.h>

typedef struct string{
    char* s;
    int len;
} string_t;

static inline void string_concat_with_char(
    string_t *s,
    allocator_t *allocator,
    char** array,
    int array_len,
    char concat_char
) {
    int total_length = 0;
    for (int i = 0; i < array_len; i++) {
        total_length += strlen(array[i]);
    }
    total_length += (array_len -1) + 1;

    s->s = mem_alloc_impl(allocator, total_length);
    s->len = total_length;

    for (int i = 0; i < array_len; i++) {
        s->s = strcat(s->s, array[i]);
        s->s = strcat(s->s, &concat_char);
    }

}
