#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include<stdio.h>
#include <stdint.h>
#include <assert.h>
#include "util/alloc.h"
#include "util/arraylist.h"
#include "util/llist.h"
#include "util/fixedlist.h"
#include "state.h"
#include "entity.h"
#include "level.h"
#include "tile.h"
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include "util/serde.h"

#define GRAVITY 0.2

typedef struct block {
    int data;
    LLIST_NODE(struct block) node;
} block_t;

typedef struct block_list block_list_t;

typedef struct {
    int x, y;
} vec2;

FIXEDLIST(float, 10) list;

state_t state;

int main(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "CC");

    entity_init();
    level_t test;
    //level_new_init(&test, 0, 10, 10);
    load_level_from_file("levels/test.clvl", &test);
    level_print(&test);

    entity_t player =  {
        .type = ENTITY_PLAYER,
        .pos = (Vector2){100, 200},
        .vel = (Vector2){0, 0},
        .rotation = 0,
        .texture = LoadTexture("assets/golbin1.png"),

    };
    level_add_entity(&test, &player);
    level_print(&test);

    allocator_t a;
    arena_allocator_init(&a, 1024);

    list.arr[1] = 10;

    int* list = mem_alloc(&a, 2 * sizeof(int));
    list[0] = 10;
    list[1] = 20;


    Camera2D camera = {
        .zoom = 1.0,
        .offset = {0, 0},
        .target = {0, 0},
        .rotation = 0.0,
    };

    while (!WindowShouldClose()) {
        level_update(&test);
        BeginDrawing();
        ClearBackground(GRAY);
        BeginMode2D(camera);
        if (GuiButton((Rectangle){20, 30, 35, 50}, "PRESS ME")) {
            printf("pressed\n");
        }
        level_render(&test);
        EndMode2D();

        EndDrawing();
    }
    level_deinit(&test);
    mem_free(&a);
}
