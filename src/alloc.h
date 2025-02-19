#ifndef ALLOC_H
#define ALLOC_H

#pragma once

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
//
// Allocate X amount of data;
//
// -------------------------
// |XXXXXXX                |
// |XXXXXXX                |
// -------------------------
// ^       ^
// Data    Ptr
//
// -------------------------
// |XXXXXXXXXXXXXXXXX      |
// |XXXXXXXXXXXXXXXXX      |
// -------------------------
// ^                ^
// Data             Ptr
//
//
// ResetArena
// -------------------------
// |XXXXXXXXXXXXXXXXX      |
// |XXXXXXXXXXXXXXXXX      |
// -------------------------
// ^
// Data/Ptr
//
// We move the pointer back to the original location and
// reset the capacity. We then overwrite all the previous
// data. Only at the end of the arena do we free everything
// completely.

typedef struct {
    void* data;
    char* ptr;
    int capacity, size;
} arena_t;

// This takes a zero initialized arena_t
// and a capacity, which is the number of
// bytes the arena will hold total.
void ArenaNew(arena_t* arena, int size) {
    arena->data = malloc(size);
    arena->ptr = arena->data;
    arena->capacity = 0;
    arena->size = size;
}

void ArenaReset(arena_t* arena) {
    arena->ptr = arena->data;
}

void *ArenaAllocate(arena_t* arena, int size) {
    void *ptr = arena->ptr;
    if (sizeof(arena->ptr) + size > arena->size){
        return NULL;
    }
    arena->ptr = arena->ptr + size;
    arena->capacity += size;
    return ptr;
}

void ArenaFree(arena_t* arena) {
    free(arena->data);
    free(arena);
}

#endif
