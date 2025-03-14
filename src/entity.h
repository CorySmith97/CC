#pragma once

#include <stdint.h>
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "forward.h"

// FUNCTION PROTOYPES
void entity_init(void);


// TYPE DEFINITIONS

typedef enum {
    ENTITY_PLAYER = 0,
    ENTITY_GOBLIN = 1,
} entity_type_e;

// entity_type_t default info all entities metadata.
// This will have rectangles, as well as will store
// all the function pointers for that type of entity.
//
// Another way to think of this is as the static info
// about all entities of a type. The info that never
// changes.

// MUST HAVES FOR ALL ENTITIES
typedef struct entity_type {
    // Name of type
    const char* name;

    // Axis Aligned Bounding Box
    // Used for collision.
    Rectangle aabb;

    // Scalar to fit different size textures within
    // the grid size that we will use.
    int scale;

    // Function to render an entity. May change based
    // on entity
    void (*render_fn)(const entity_t*);
    // Function that is used to update entity every frame.
    void (*update_fn)(level_t*, entity_t*);
    // Function used for setting network packets each
    // server tick
    void (*tick_fn)(level_t*, entity_t*);
} entity_type_t;

// This is the entity stuff that changes per instance of
// an entity.

typedef struct entity {
    // Enum for entity type. Used to get entity_type_t
    // from the entity list.
    entity_type_e type;

    // position middle bottom of sprite
    Vector2 pos, vel, render_pos;
    float rotation;
    Texture2D texture;

    struct {
        bool can_jump;
    } player_t;

    struct {
        int ammo_count;
    } goblin_t;

} entity_t;

extern entity_type_t ENTITY_TYPES[ENTITY_COUNT];
#define ENTITY_TYPE(_T) ((const entity_type_t*) &ENTITY_TYPES[(_T).type])

