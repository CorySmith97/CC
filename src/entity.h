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

typedef struct entity entity_t;
typedef struct position position_t;
typedef struct sprite_atlas sprite_atlas_t;
typedef struct entity_list entity_list_t;
typedef struct component component_t;

void EntityCreate(entity_t* entity);
void EntityAddPosition(entity_t* entity, position_t pos);
void EntityAddSprite(entity_t* entity, sprite_atlas_t sprite);

#endif
