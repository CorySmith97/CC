#pragma once

#include "alloc.h"
#include "kvstore.h"
#include "strings.h"
#include "type.h"
#include <stddef.h>

typedef struct map {
    allocator_t *allocator;
    string_t* keys;
    any_t* values;
    size_t size;
} map_t;

static inline hash_t hash_fn(string_t key) {
    hash_t hash = 0x100;

    for (hash_t i = 0; i < key.len; i++) {
        hash ^= hash + key.s[i];
    }
    return hash;
}

static inline void map_init(
    map_t *map,
    allocator_t *allocator,
    size_t initial_size
) {
    *map = (map_t) {
        .allocator = allocator,
        .keys = mem_alloc_impl(allocator, initial_size * sizeof(string_t)),
        .values = mem_alloc_impl(allocator, initial_size * sizeof(any_t)),
        .size = initial_size,
    };
}

static inline void map_add_value(
    map_t *map,
    string_t key,
    any_t value
) {
    const hash_t hash = hash_fn(key) % map->size;
    map->keys[hash] = key;
    map->values[hash] = value;
}

static inline any_t* map_get_value(
    map_t *map,
    string_t key
) {
    const hash_t hash = hash_fn(key) % map->size;
    return &map->values[hash];
}

static inline void map_deinit(
    map_t *map
) {
    mem_free(map->allocator);
}
