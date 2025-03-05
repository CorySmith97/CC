#include "tile.h"
#include "forward.h"

void tile_tick_ground(const tile_t* tile) {
}
void tile_update_ground(const tile_t* tile) {
}
void tile_render_ground(const tile_t* tile) {
    tile_type_t type = TILE_TYPES[tile->type];
    Rectangle rec = spritesheet_get_rec_from_id(type.ss, type.sprite_id);
    DrawTextureRec(type.ss->texture, rec, tile->pos, RAYWHITE);
}

tile_type_t TILE_TYPES[TILE_COUNT];

void tiles_init(void){
    TILE_TYPES[TILE_GROUND] = (tile_type_t) {
        .name = "Ground",
        .aabb = (Rectangle){0, 0, 16, 16},
        .flags = 0,
        .tick_fn = tile_tick_ground,
        .render_fn = tile_render_ground,
        .update_fn = tile_update_ground,
        .ss = &ss,
        .sprite_id = 0,
    };
    TILE_TYPES[TILE_SAND] = (tile_type_t) {
        .name = "Sand",
        .aabb = (Rectangle){0, 0, 16, 16},
        .flags = 0,
        .tick_fn = tile_tick_ground,
        .render_fn = tile_render_ground,
        .update_fn = tile_update_ground,
        .ss = &ss,
        .sprite_id = 1,
    };
}


