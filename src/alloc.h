#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

// Basics of an Arena Allocator
//
// Chunk of memory
// -------------------------
// |                       |
// |                       |
// -------------------------
// ^
// Data

typedef struct {
    void* data;
    void* ptr;
    int capacity;
} arena_t;

// This takes a zero initialized arena_t
// and a capacity, which is the number of
// bytes the arena will hold total.
void NewArena(arena_t* arena, int capacity) {
    arena->data = malloc(capacity);
    arena->ptr = arena->data;
    arena->capacity = capacity;
}

#endif
