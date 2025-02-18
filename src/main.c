#include "../lib/raylib.h"

typedef struct {
    void* data;
    int len, stride;
} array_t;

int main(){
    InitWindow(800, 600, "CC");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Deez Nuts", 10, 10, 12, BLACK);
        EndDrawing();
    }
}
