#include "editor.h"
#include "level.h"
#include "state.h"
#include "util/alloc.h"
#include <stdlib.h>

static bool new_level_width_selected = false;
static bool new_level_height_selected = false;
static bool new_level_secret = false;
int list_view = 0;
int list_view_active = 0;

char *name;

void editor_init(editor_t *e){
    allocator_t a;
    arena_allocator_init(&a, PAGE_SIZE * 100);
    name = mem_alloc(&a, 100);

    string_t st;
    FilePathList list = LoadDirectoryFiles("levels");

    Camera2D camera = {
        .zoom = 1.0,
        .offset = {0, 0},
        .target = {0, 0},
        .rotation = 0.0,
    };

    string_concat_with_char(&st, &a, list.paths, list.count, ';');

    *e = (editor_t) {
        .camera = camera,
        .editor_window = (Rectangle){ 5, 15, 250, 300},
        .new_level_window = (Rectangle){ 200, 200, 250, 300},
        .tile_editor_window = (Rectangle){ 5, 15, 250, 300},
        .editor_window_toggle = true,
        .new_level_window_toggle = false,
        .selected_level = nullptr,
        .levels = st,
        .allocator = a,
    };
}

void editor_reload_levels(editor_t *e) {
}

void editor_render(editor_t *e){
    LOG(debug, TextFormat("%d", state.levels.size));

    bool editor_moving = false;
    bool new_level_moving = false;
    Vector2 mouse_pos = GetMousePosition();

    BeginMode2D(e->camera);
    if (e->selected_level != nullptr) {
        level_render(e->selected_level);
    }
    EndMode2D();

    Rectangle status_bar_collision_rec =
        (Rectangle){e->editor_window.x, e->editor_window.y,
                    e->editor_window.width, 24};
    Rectangle new_level_bar_collision_rec =
        (Rectangle){e->new_level_window.x, e->new_level_window.y,
                    e->new_level_window.width, 24};
    if (CheckCollisionPointRec(mouse_pos, status_bar_collision_rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        editor_moving = true;
    }
    if (CheckCollisionPointRec(mouse_pos, new_level_bar_collision_rec) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        new_level_moving = true;
    }

    if (editor_moving) {
        Vector2 delta = GetMouseDelta();
        e->editor_window.x += delta.x;
        e->editor_window.y += delta.y;
    }
    if (new_level_moving) {
        Vector2 delta = GetMouseDelta();
        e->new_level_window.x += delta.x;
        e->new_level_window.y += delta.y;
    }

    if (e->editor_window_toggle) {
        e->editor_window_toggle = !GuiWindowBox(e->editor_window, "Editor");
        if (e->selected_level) {
            DrawText(TextFormat("Current level id: %d", e->selected_level->id), e->editor_window.x + 30, e->editor_window.y + 30, 12, RAYWHITE);
        } else {
            DrawText("No selected level", e->editor_window.x + 30, e->editor_window.y + 30, 12, RAYWHITE);
        }
        if (GuiButton((Rectangle){
            e->editor_window.x + 140, e->editor_window.y + 30,
            80, 40,
        }, "New Level")) {
            e->new_level_window_toggle = !e->new_level_window_toggle;
        }

        GuiListView((Rectangle){e->editor_window.x + 30, e->editor_window.y + 150,
            160, 70}, e->levels.s, &list_view, &list_view_active);

    }
    if (e->tile_editor_window_toggle) {
        e->tile_editor_window_toggle = !GuiWindowBox(e->tile_editor_window, "Tile");
        DrawText(TextFormat("Selected tile: %d", e->selected_tile), e->tile_editor_window.x + 30, e->tile_editor_window.y + 30, 12, RAYWHITE);
        Rectangle rec = (Rectangle){ e->tile_editor_window.x + 140, e->tile_editor_window.y + 30, 80, 40};
        GuiSpinner(rec, "Tile type", &e->selected_level->tiles[e->selected_tile].type, 0, 4, true);
    }
    if (e->new_level_window_toggle) {
        e->new_level_window_toggle = !GuiWindowBox(e->new_level_window, "New Level");
        Rectangle new_width_rec = (Rectangle){e->new_level_window.x + 120, e->new_level_window.y + 30,
                100, 40};
        Rectangle new_height_rec = (Rectangle){e->new_level_window.x + 120, e->new_level_window.y + 80,
            100, 40};
        Rectangle new_name_rec = (Rectangle){e->new_level_window.x + 40, e->new_level_window.y + 130,
            200, 120};
        new_level_width_selected = CheckCollisionPointRec(mouse_pos, new_width_rec);
        new_level_height_selected = CheckCollisionPointRec(mouse_pos, new_height_rec);
        GuiSpinner(
            new_width_rec, "New Level width", &e->new_level_width, 0, 256, new_level_width_selected);
        GuiSpinner(
            new_height_rec, "New Level height", &e->new_level_height, 0, 256, new_level_height_selected);
        int res = GuiTextInputBox(
            new_name_rec,nullptr, nullptr, "Ok;Cancel", name, 12, nullptr);
        if (res == 1) {
            LOG(info, TextFormat("SAVED: %s", name));
        }
        if (GuiButton((Rectangle){e->new_level_window.x + 10, e->new_level_window.y + 260, 100, 30}, "Create Level")) {
            e->selected_level = malloc(sizeof(level_t));
            if (e->selected_level == nullptr) {
                LOG(error, "THIS HOE FAILED");
            }
            level_new_init(e->selected_level, 0, e->new_level_width, e->new_level_height);
            e->new_level_window_toggle = false;
        }
    }
}
void editor_input(editor_t *e){
    Vector2 mouse_pos = GetMousePosition();
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), e->camera);
    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        // Get the world point that is under the mouse

        // Set the offset to where the mouse is
        e->camera.offset = GetMousePosition();

        // Set the target to match, so that the e->camera maps the world space point
        // under the cursor to the screen space point under the cursor at any zoom
        e->camera.target = mouseWorldPos;

        // Zoom increment
        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
        e->camera.zoom = Clamp(e->camera.zoom*scaleFactor, 0.125f, 64.0f);
    }
    // Zoom based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        LOG(info, "ARE WE CLICKING");
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/e->camera.zoom);
        e->camera.target = Vector2Add(e->camera.target, delta);
    }
    if (IsKeyPressed(KEY_FIVE)) {
        e->editor_window_toggle = true;
    }
    if (e->selected_level) {
        for (int i = 0; i < e->selected_level->tile_count; i++) {
            Rectangle rec = (Rectangle){
                .x = e->selected_level->tiles[i].pos.x,
                .y = e->selected_level->tiles[i].pos.y,
                .height = 16,
                .width = 16,
            };
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouseWorldPos, rec)) {
                e->tile_editor_window_toggle = true;
                e->selected_tile = i;
            }

        }
        LOG(info, TextFormat("Selected tile: %d", e->selected_tile));
    }

}

void editor_deinit(editor_t *e){
    e->allocator.free_fn(&e->allocator);
}
