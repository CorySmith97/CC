#include "level.h"
#include "forward.h"
#include "tile.h"
#include "util/log.h"
#include <stdio.h>

void level_new_init(level_t *l,
                    uint32_t id,
                    int width,
                    int height) {
    *l = (level_t){
        .id = id,
        .entities = malloc(sizeof(entity_t)),
        .entity_count = 0,
        .tiles = malloc(width * height * sizeof(tile_t)),
        .tile_count = width * height,
        .width = width,
        .height = height,
    };
    for (int i = 0; i < l->tile_count; i++) {
        l->tiles[i] = (tile_t) {
            .pos = (Vector2){.x = (i % width) * 16, .y = (i / height) * 16},
            .size = (Vector2){16, 16},
            .type = TILE_GROUND,
        };
    }
}

void level_deinit(level_t *t) {
    free(t->entities);
}

void level_update(level_t *t) {
    for (int i = 0; i < t->entity_count; i++) {
        const entity_type_t* type = ENTITY_TYPE(t->entities[i]);
        type->update_fn(t, &t->entities[i]);
    }
}
void level_tick(level_t *t) {
    for (int i = 0; i < t->entity_count; i++) {
        const entity_type_t* type = ENTITY_TYPE(t->entities[i]);
        type->tick_fn(t, &t->entities[i]);
    }
}
void level_render(level_t *t) {
    if (t != NULL) {
        level_print(t);
        if (t->tile_count > 0) {
            for (int i = 0; i < t->tile_count; i++) {
                const tile_type_t* type = TILE_TYPE(t->tiles[i]);
                if (type) {
                    type->render_fn(&t->tiles[i]);
                }
            }
        }

        if (t->entity_count > 0) {
            for (int i = 0; i < t->entity_count; i++) {
                const entity_type_t* type = ENTITY_TYPE(t->entities[i]);
                if (type) {
                    type->render_fn(&t->entities[i]);
                }
            }
        }
    }
}

void level_add_entity(level_t *t, entity_t *e) {
    void* temp = realloc(t->entities, sizeof(entity_t) * (t->entity_count + 1));
    if (temp == NULL) {
        free(t->entities);
        printf("Printing error from realloc\n");
    }else if (temp == t->entities) {
        temp = NULL;
    } else {
        t->entities = (entity_t*)temp;
        temp = NULL;
    }

    t->entities[t->entity_count] = *e;
    t->entity_count += 1;
}

void level_print(level_t *t) {
    printf("id: %d\ntile count: %d\nentity count: %d\n", t->id, t->tile_count, t->entity_count);
}
