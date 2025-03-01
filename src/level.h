#pragma once

#include "entity.h"
#include "forward.h"
#include <stdlib.h>
#include <stdint.h>
#include "tile.h"
#include <stdio.h>
#include "util/log.h"

// FUNCTION PROTOYPES

void level_new_init(level_t *l, uint32_t id, int width, int height);
void level_tick(level_t *t);
void level_update(level_t *t);
void level_render(level_t *t);
void level_deinit(level_t *t);
void level_add_entity(level_t *t, entity_t *e);
void level_print(level_t *t);

// TYPE DEFINITIONS

typedef struct level{
    uint32_t id;
    int width, height;

    entity_t *entities;
    int entity_count;
    // list of all tiles.
    tile_t *tiles;
    int tile_count;
} level_t;


