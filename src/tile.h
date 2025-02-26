#pragma once

#include "forward.h"
#include "../lib/raylib.h"

#define TILE_COUNT 1

#define TILE_SPAWNER 0x01
#define TILE_EMITTER 0x02

// FUNCTION PROTOYPES
void tiles_init(void);

typedef enum tile_enum {
    TILE_GROUND,
} tile_type_e;

typedef struct tile_type{
    const char* name;
    // Axis Aligned Bounding Box
    Rectangle aabb;
    // Render for type
    void (*render_fn)(const tile_t*);

    // Update for tile. Used for collision or
    // event triggers
    void (*update_fn)(const tile_t*);

    void (*tick_fn)(const tile_t*);

    int flags;
} tile_type_t;

extern tile_type_t TILE_TYPES[TILE_COUNT];
#define TILE_TYPE(_T) ((const tile_type_t*) &TILE_TYPES[(_T).type])


typedef struct tile {
    tile_type_e type;


    Vector2 pos;
} tile_t;
