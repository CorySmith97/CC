#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "forward.h"
#include "spritesheet.h"
#include "util/alloc.h"
#include "util/arraylist.h"
#include "util/kvstore.h"
#include "util/llist.h"
#include "util/fixedlist.h"
#include "state.h"
#include "entity.h"
#include "level.h"
#include "tile.h"
#include "util/log.h"
#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"
#include "util/serde.h"
#include "../lib/styles/dark/style_dark.h"
#include "editor.h"
#include "def.h"
#include "util/strings.h"
#include "util/map.h"

#define GRAVITY 0.2

state_t state;
spritesheet_t ss;

FIXEDLIST(float, 10) list;

int main(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CC");
    state_init(&state);

    editor_t editor;
    editor_init(&editor);
    tiles_init();

    //level_t test_level;
    //level_new_init(&test_level, 1, 32, 32);
    //save_level_to_file("levels/test2.clvl", &test_level);
    level_t l;
    load_level_from_file("levels/test2.clvl", &state.arena, &l);
    printf("Level: %d, %d", l.tile_count, l.entity_count);

    entity_init();
    level_t test;
    level_new_init(&test, 0, 10, 10);
    //load_level_from_file("levels/test.clvl", &test);
    //level_print(&test);
    //
    spritesheet_init(&ss, "assets/cctilesheet.png", 16, 16);

    entity_t player =  {
        .type = ENTITY_PLAYER,
        .pos = (Vector2){100, 200},
        .vel = (Vector2){0, 0},
        .rotation = 0,
        .texture = LoadTexture("assets/golbin1.png"),
    };

    tile_t ground = {
        .type = TILE_GROUND,
        .size = (Vector2){16, 16},
        .pos = (Vector2){400, 200},
    };
    level_add_entity(&test, &player);

    allocator_t a;
    arena_allocator_init(&a, 1024);

    GuiLoadStyleDark();

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

    SetTargetFPS(120);
    while (!WindowShouldClose()) {
        //LOG(info, TextFormat("%fms", GetFrameTime()));
        if (IsKeyPressed(KEY_L)) {
            state.menu_state = MAIN_MENU;
        }
        switch (state.menu_state) {
            case MAIN_MENU: {
                BeginDrawing();
                ClearBackground(GRAY);
                DrawText("CC", (SCREEN_WIDTH / 2) - 20, 200, 20, BLACK);
                DrawText("Press 'l' to return to main menu", 10, 20, 10, BLACK);
                if (GuiButton((Rectangle){(SCREEN_WIDTH / 2) - 45, 300, 90, 30}, "Level Editor")) {
                    state.menu_state = LEVEL_EDITOR;
                }
                if (GuiButton((Rectangle){(SCREEN_WIDTH / 2) - 45, 350, 90, 30}, "Scratch")) {
                    state.menu_state = SCRATCH;
                }
                EndDrawing();
            } break;
            case LEVEL_EDITOR: {
                editor_input(&editor);
                BeginDrawing();
                ClearBackground(GRAY);
                const tile_type_t* type = TILE_TYPE(ground);
                if (type) {
                    type->render_fn(&ground);
                }
                editor_render(&editor);
                EndDrawing();
            } break;
            case SCRATCH: {
                BeginDrawing();
                ClearBackground(GRAY);
                BeginMode2D(camera);
                if (GuiButton((Rectangle){20, 30, 80, 50}, "PRESS ME")) {
                    printf("pressed\n");
                }
                EndMode2D();
                EndDrawing();
            } break;

        }
        printf("\e[1;1H\e[2J");
    }
    level_deinit(&test);
    editor_deinit(&editor);
    mem_free(&a);
    state_deinit(&state);
}
