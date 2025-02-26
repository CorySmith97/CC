#pragma once

#include "../lib/raylib.h"
#include "util/fixedlist.h"

typedef struct state {
    FIXEDLIST(Texture2D, 10) textures;
} state_t;
