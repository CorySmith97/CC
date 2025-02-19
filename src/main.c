#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include <stdint.h>
#include "alloc.h"

#define GRAVITY 0.2

typedef struct {
    void* data;
    int len, stride;
} array_t;

typedef struct {
    Texture2D texture;
    Vector2 pos;
    uint32_t spritesheet_id;
} sprites_t;

typedef struct {
    Vector2 pos, vel;
    float speed;
} entity_t;

int main(){
    arena_t a = {};
    ArenaNew(&a, 4096);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "CC");

    Camera2D camera = {
        .zoom = 1.0,
        .offset = {0, 0},
        .target = {0, 0},
        .rotation = 0.0,
    };

    entity_t p1 = {
        .speed = 0.005,
        .pos = {.x = 400, .y = 300},
    };

    while (!WindowShouldClose()) {
        int* data = ArenaAllocate(&a, 10 * sizeof(int));
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawRectangleV(p1.pos, (Vector2){10, 10}, BLUE);
        EndMode2D();

        for (int i = 0; i < 10; i++) {
            DrawText(TextFormat("%d", data[i]), 10, 10 + (i * 12), 12, BLACK);
        }
        EndDrawing();
        ArenaReset(&a);
    }
    ArenaFree(&a);
}
