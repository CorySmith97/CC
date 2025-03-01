#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "forward.h"
#include "util/alloc.h"
#include "util/arraylist.h"
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

#define GRAVITY 0.2


FIXEDLIST(float, 10) list;

static state_t state;

int main(void){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CC");


    editor_t editor;
    editor_init(&editor);

    entity_init();
    level_t test;
    level_new_init(&test, 0, 10, 10);
    //load_level_from_file("levels/test.clvl", &test);
    //level_print(&test);

    entity_t player =  {
        .type = ENTITY_PLAYER,
        .pos = (Vector2){100, 200},
        .vel = (Vector2){0, 0},
        .rotation = 0,
        .texture = LoadTexture("assets/golbin1.png"),
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
        LOG(info, TextFormat("%fms", GetFrameTime()));
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
                editor_render(&editor);
                EndDrawing();
            } break;
            case SCRATCH: {
                level_update(&test);
                BeginDrawing();
                ClearBackground(GRAY);
                BeginMode2D(camera);
                if (GuiButton((Rectangle){20, 30, 80, 50}, "PRESS ME")) {
                    printf("pressed\n");
                }
                editor_render(&editor);
                level_render(&test);
                EndMode2D();
                EndDrawing();
            } break;

        }
    }
    level_deinit(&test);
    editor_deinit(&editor);
    mem_free(&a);
}
