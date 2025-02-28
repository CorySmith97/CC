#pragma once
#include "llist.h"
#include <stddef.h>
#include <stdio.h>

#include <stdlib.h>

typedef struct allocator allocator_t;

#define mem_alloc mem_alloc_impl
#define mem_free mem_free_impl

static inline void *mem_alloc_impl(allocator_t *a, size_t size);
static inline void mem_free_impl(allocator_t *a);

typedef struct allocator_stats {
    size_t size;
} allocator_stats_t;

typedef struct allocator_mem_block {
    LLIST_NODE(struct allocator_mem_block) node;
    int blocks_used, total_used;
} allocator_mem_block_t;

typedef struct allocator {
    void *(*alloc_fn)(allocator_t*, size_t);
    void (*free_fn)(allocator_t*);

    allocator_stats_t stats;

    union {
        struct {
            void *data;
            char *ptr;
            size_t size, capacity;
        } arena_allocator;
        struct {
            size_t size, capacity, largest;
            LLIST(allocator_mem_block_t) blocks;
        } page_allocator;
        struct {
            void *data;
            int size, capacity;
        } bump;
    };
} allocator_t;


#ifdef ALLOC_IMPL
static void _page_allocator_init(allocator_t *a, int n) {
    n = multround_up_to_mult(n, MAXMAX_ALIGN);

    allocator_mem_block_t block = a->page_allocator.blocks.head;

    if (!block || block->capacity + n > block->size) {
        const int size = max(a->page_allocator.largest, n);

        block = mem_alloc(
            a->page_allocator.parent,
            size + sizeof(allallocator_mem_block_t));

        block->size = size;
        block->used = 0;
        llist_init_node(&block->node);
        llistllist_prepend(node, &a->page_allocator.blocks, block);
    }
}
#endif

typedef struct {
    void* data;
    char* ptr;
    int capacity, size;
} arena_t;

// This takes a zero initialized arena_t
// and a capacity, which is the number of
// bytes the arena will hold total.
static inline void ArenaNew(arena_t* arena, int size) {
    arena->data = malloc(size);
    arena->ptr = arena->data;
    arena->capacity = 0;
    arena->size = size;
}

static inline void ArenaReset(arena_t* arena) {
    arena->ptr = arena->data;
}

static inline void *_arena_allocate(allocator_t* a, size_t size) {
    void *ptr = a->arena_allocator.ptr;
    if (sizeof(a->arena_allocator.ptr) + size > a->arena_allocator.capacity){
        return NULL;
    }
    a->arena_allocator.ptr = a->arena_allocator.ptr + size;
    a->arena_allocator.size += size;
    return ptr;
}

static inline void _arena_free (allocator_t* a) {
    free(a->arena_allocator.data);
    a->arena_allocator.data = NULL;
    a->arena_allocator.ptr = NULL;
    a->arena_allocator.capacity = 0;
    a->arena_allocator.size = 0;
}


static inline void arena_allocator_init(allocator_t *a, size_t capacity) {
    *a = (allocator_t){
        .stats = {},
        .alloc_fn = _arena_allocate,
        .free_fn = _arena_free,
        .arena_allocator = {
            .data = malloc(capacity),
            .size = 0,
            .capacity = capacity,
        }
    };
    a->arena_allocator.ptr = a->arena_allocator.data;
}

static inline void *mem_alloc_impl(allocator_t *a, size_t size) {
    void *data = a->alloc_fn(a, size);
    return data;
}
static inline void mem_free_impl(allocator_t *a) {
    a->free_fn(a);
}
