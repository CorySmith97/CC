#ifndef COMPONENTS_H
#define COMPONENTS_H

//To add a component you simple typedef a struct,
//and make sure there is an ID in the struct.
//IE:
//
//typedef struct {
//  uint32_t entity_id;
//  void* data_for_type;
//} entity_type_t;

#include <stdint.h>
#include "../lib/raylib.h"

typedef struct {
    uint32_t entity_id;
    Vector2 vec;
} position_t;

typedef struct {
    uint32_t entity_id;
    Texture2D texture;
} sprite_altas_t;

typedef struct {
    position_t position[100];
} entity_list_t;

typedef struct {
} component_t;

void CreateEntity(entity_list_t* entity_list) {

}

#endif
