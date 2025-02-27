#include "tile.h"
#include "forward.h"

void tile_tick_ground(const tile_t* tile) {
}
void tile_update_ground(const tile_t* tile) {
}
void tile_render_ground(const tile_t* tile) {
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
    };
}
