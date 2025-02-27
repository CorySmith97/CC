#pragma once

#include "../lib/raylib.h"
#include "util/alloc.h"
#include "util/fixedlist.h"

typedef struct state {
    allocator_t arena;
    FIXEDLIST(Texture2D, 10) textures;
} state_t;
