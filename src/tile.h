#pragma once

#include "forward.h"
#include "../lib/raylib.h"

// FUNCTION PROTOYPES
void tiles_init(void);

// TYPE DEFINITIONS
#define TILE_SIZE (Vector2){16, 16}

// Flags for tile. These are bit flags.
// use like: TILE_SPAWNER | TILE_EMITTER
#define TILE_SPAWNER 0x01
#define TILE_EMITTER 0x02

// Size of tile_type_e
#define TILE_COUNT 1

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

    // BIT FLAGS
    int flags;
} tile_type_t;

extern tile_type_t TILE_TYPES[TILE_COUNT];
#define TILE_TYPE(_T) ((const tile_type_t*) &TILE_TYPES[(_T).type])

typedef struct tile {
    tile_type_e type;

    Vector2 pos, size;
    spritesheet_t *ss;
} tile_t;
