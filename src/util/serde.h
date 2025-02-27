#pragma once

/* SERIALIZE/DESERIALIZE */

#include "../level.h"
#include <stdint.h>
#include <stdio.h>
#include "../forward.h"

void save_level_to_file(
    const char* file_path,
    level_t *level) {

    FILE *f = fopen(file_path, "wb");
    if (f == NULL) {
        return;
    }
    fwrite(&level->id, sizeof(uint32_t), 1, f);
    fwrite(&level->width, sizeof(int), 1, f);
    fwrite(&level->height, sizeof(int), 1, f);

    fwrite(&level->entity_count, sizeof(int), 1, f);
    for (int i = 0; i < level->entity_count; i++) {
        fwrite(&level->entities[i], sizeof(entity_t), 1, f);
    }
    fwrite(&level->tile_count, sizeof(int), 1, f);
    for (int i = 0; i < level->tile_count; i++) {
        fwrite(&level->tiles[i], sizeof(tile_t), 1, f);
    }
    fclose(f);
}
void load_level_from_file(
    const char* file_path,
    level_t *level) {
    FILE *f = fopen(file_path, "rb");
    if (f == NULL) {
        return;
    }
    fread(level, sizeof(level_t), 1, f);
    fclose(f);
}
