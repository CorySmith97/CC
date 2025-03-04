#include "spritesheet.h"


void spritesheet_init(
    spritesheet_t* ss,
    const char* path,
    int sprite_width,
    int sprite_height) {

    Texture2D texture = LoadTexture(path);
    *ss = (spritesheet_t) {
        .texture = texture,
        .sprite_width = sprite_width,
        .sprite_height = sprite_height,
    };
}

Rectangle spritesheet_get_rec_from_id(
    spritesheet_t *ss,
    int id) {
    return (Rectangle){
        .x = (ss->texture.width % ss->sprite_width) * id,
        .y = (ss->texture.height % ss->sprite_height) * id,
        .width = ss->sprite_width,
        .height = ss->sprite_height,
    };
}
