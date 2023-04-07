/*
    The Sprite is a graphical object, image, animation, ets.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <string.h>
#include "typedef.h"
#include "transfor.h"
#include "entity.h"
#include "assets.h"

// NOTE: these probably need to be tweaked later
#define MAX_SPRITE_FRAMES 255    // Maximum total number of frames a sprite can hold
#define MAX_ANIMATION_FRAMES 255 // Maximum number of frames of an animation
#define MAX_ANIMATIONS 10        // Maximum number of animations a sprite can have

// ENUMS

typedef enum Step_Rotation
{
    DEFAULT,  // 0 deg
    UP,       // 90 deg
    REVERSED, // 180 deg
    DOWN,     // 270 deg
} Step_Rotation;

// STRUCTURES

typedef struct animation_type
{
    char id[32];
    uint frames[MAX_ANIMATION_FRAMES]; // Array of indexes to the sprite frames
    int repeat;                        // -1 = infinite loop, 0 = play once, 1..max = repeat n times
    int current_repeat;
    char jojo;
    char jojo_direction;
    float frame_time;
    float current_time;
    float duration;
} animation, *animation_ptr;

// THis is the default sprite type
typedef struct sprite_type
{
    Entity_Type type;                         // The type of sprite, should be Entity_Type.SPRITE_FRAME
    char id[32];                              // Id/name of the sprite, optional but good if you need to search for this sprite
    vec2 position;                            // The sprite local position based on its center
    vec2f scale;                              // Will see later if I'll implement a proper scale
    float rotation;                           // As with scale above
    Step_Rotation step_rotation;              // A fixed 90° step rotation, because that's just rendering the pixels in a different order
    vec2 mirror;                              // To mirror the sprite in x,y direction
    sprite_sheet_asset_ptr asset;             // Pointer to the sprite sheet asset
    uint current_frame;                       // The frame that should be rendered, -1 => should not render anything
    uint current_animation;                   // -1 == no animation is playing
    animation_ptr animations[MAX_ANIMATIONS]; // List of all animations the sprite has
} sprite, *sprite_ptr;

typedef struct sprite_image_type
{
    Entity_Type type; // The type of sprite, should be Entity_Type.SPRITE_IMAGE
    char id[32];
    vec2 position;
    vec2f scale;
    float rotation;
    Step_Rotation step_rotation;
    vec2 mirror;
    image_asset_ptr asset;
} sprite_image, *sprite_image_ptr;

// This is a custom sprite that only renders full screen images
typedef struct sprite_full_screen_type
{
    Entity_Type type;          // The type of sprite, should be Entity_Type.SPRITE_SCREEN, will for example be used to determine which renderer to use
    char id[32];               // Id/name of the sprite
    image_asset_ptr asset;     // The image data to render, needs to be SCREEN_WIDTH x SCREEN_HEIGHT in size
    palette_asset_ptr palette; // If not NULL use this palette
} sprite_full_screen, *sprite_full_screen_ptr;

// PROTOTYPES
sprite_ptr Init_Sprite(char *id, sprite_sheet_asset_ptr asset);
void Render_Sprite(sprite_ptr sprite);

// INTERNALS
static void Render_Transparent_Sprite(sprite_ptr sprite);
static void Render_Opaque_Sprite(sprite_ptr sprite);

#endif