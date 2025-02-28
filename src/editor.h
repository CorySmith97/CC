#pragma once

#include "forward.h"
#include "util/strings.h"
#include "../lib/raygui.h"
#include "level.h"
#include "util/alloc.h"
#include <stddef.h>
#include <stdio.h>
#include "def.h"

// FUNCTION PROTOYPES

void editor_init(editor_t*);
void editor_render(editor_t*);
void editor_input(editor_t*);
void editor_reload_levels(editor_t*);

// TYPE DEFINITIONS

typedef struct editor {
    allocator_t allocator;

    Rectangle editor_window;
    Rectangle new_level_window;

    bool editor_window_toggle;
    bool new_level_window_toggle;

    string_t levels;
    int levels_len;
    level_t *selected_level;
    int new_level_width, new_level_height;
} editor_t;
