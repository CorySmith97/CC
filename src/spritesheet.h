#pragma once

#include "forward.h"
#include "../lib/raylib.h"

extern spritesheet_t ss;

// FUNCTION PROTOYPES
void spritesheet_init(
    spritesheet_t* ss,
    const char* path,
    int sprite_width,
    int sprite_height);

Rectangle spritesheet_get_rec_from_id(
    spritesheet_t *ss,
    int id);

// TYPE DEFINITIONS

typedef struct spritesheet{
    Texture2D texture;
    int sprite_width, sprite_height;
} spritesheet_t;
