#pragma once

#include "forward.h"
#include "../lib/raylib.h"
#include "util/alloc.h"
#include "util/fixedlist.h"
#include "level.h"
#include "editor.h"
#include "def.h"

typedef enum {
    MAIN_MENU,
    LEVEL_EDITOR,
    SCRATCH,
} menu_state_e;

typedef struct state {
    menu_state_e menu_state;
    allocator_t arena, frame;
    editor_t editor;
    level_t *active_level;
} state_t;

void state_init(state_t* s) {
    allocator_t arena;
    allocator_t frame;
    // This is 40960 bytes
    arena_allocator_init(&arena, PAGE_SIZE * 10);
    // This is 4096 bytes
    arena_allocator_init(&frame, PAGE_SIZE);

    editor_t e;
    editor_init(&e);

    *s = (state_t) {
        .arena = arena,
        .frame = frame,
        .editor = e,
        .active_level = nullptr,
        .menu_state = MAIN_MENU,
    };
}
