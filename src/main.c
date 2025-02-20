#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include <stdint.h>
#include <assert.h>
#include "util/alloc.h"
#include "util/arraylist.h"
#include "util/llist.h"

#define GRAVITY 0.2

typedef struct block {
    int data;
    LLIST_NODE(struct block) node;
} block_t;

typedef struct block_list block_list_t;

typedef struct {
    int x, y;
} vec2;

DEFINE_ARRAY_LIST(vec2);

int main(void){
    arraylist_vec2_t v;
    arraylist_vec2_init(&v);
    arraylist_vec2_push(&v, (vec2){.x = 1, .y = 1});
    allocator_t a;
    arena_allocator_init(&a, 1024);

    int* list = mem_alloc(&a, 2 * sizeof(int));
    list[0] = 10;
    list[1] = 20;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "CC");

    Camera2D camera = {
        .zoom = 1.0,
        .offset = {0, 0},
        .target = {0, 0},
        .rotation = 0.0,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawRectangle(30, 39, 100, 100, BLACK);
        EndMode2D();

        EndDrawing();
    }
    mem_free(&a);
}
