#include "entity.h"
//#define DEBUG

static void player_update(level_t *level, entity_t *e) {
    e->pos = Vector2Add(e->pos, e->vel);
    e->vel = Vector2Zero();
    if (IsKeyDown(KEY_W)) {
        e->pos.y -= 0.1;
    }
    if (IsKeyDown(KEY_S)) {
        e->pos.y += 0.1;
    }
    if (IsKeyDown(KEY_A)) {
        e->pos.x -= 0.1;
    }
    if (IsKeyDown(KEY_D)) {
        e->pos.x += 0.1;
    }
}
static void player_tick(level_t *level, entity_t *e) {
    // Networked. At the server tick rate send data to
    // server about entity.
}
static void player_render(const entity_t *e) {
    entity_type_t type = ENTITY_TYPES[e->type];
    DrawTextureEx(e->texture, e->pos, e->rotation, type.scale, RAYWHITE);
    DrawCircleV(e->pos, 3, RED);
#ifdef DEBUG
    Rectangle aabb = ENTITY_TYPE(*e)->aabb;
    DrawRectangleLinesEx((Rectangle){aabb.x + e->pos.x, aabb.y + e->pos.y, aabb.width, aabb.height}, 2, RED);
#endif
}

entity_type_t ENTITY_TYPES[ENTITY_COUNT];


// Define new entity types here.
void entity_init(void) {
    ENTITY_TYPES[ENTITY_PLAYER] = (entity_type_t) {
        .name = "player",
        .aabb = (Rectangle){.x = 0, .y = 0, .width = 10, .height = 10},
        .scale = 1.0,
        .update_fn = player_update,
        .tick_fn = player_tick,
        .render_fn = player_render,
    };
}

