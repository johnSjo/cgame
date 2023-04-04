/*
  The Entity is an object that can live in the scene
  i.e. all sub entities should mimic the entity struct
*/

#ifndef ENTITY_H
#define ENTITY_H

// ENUMS
typedef enum Entity_Type
{
  GROUP,
  PLAYER,
  SPRITE_FRAME,
  SPRITE_IMAGE,
  SPRITE_SCREEN,
} Entity_Type;

// STRUCTS

typedef struct entity_type
{
  Entity_Type type;
  char id[32];
} entity, *entity_ptr;

#endif