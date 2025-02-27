#pragma once

#include "forward.h"
#include "../lib/raylib.h"

// FUNCTION PROTOYPES
void spritesheet_init(spritesheet_t*);

// TYPE DEFINITIONS

typedef struct spritesheet{
    Texture2D texture;
    int sprite_count_row, sprite_count_height;
} spritesheet_t;
