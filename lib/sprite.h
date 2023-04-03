#ifndef SPRITE_H
#define SPRITE_H

#include "vec.h"
#include "typedef.h"
#include "frame.h"

// NOTE: these probably need to be tweaked later
#define MAX_SPRITE_FRAMES 255    // Maximum total number of frames a sprite can hold
#define MAX_ANIMATION_FRAMES 255 // Maximum number of frames of an animation
#define MAX_ANIMATIONS 10        // Maximum number of animations a sprite can have

// ENUMS

typedef enum Sprite_State
{
    IDLE,
    STILL,
} Sprite_State;

typedef enum Animation_Name
{
    WALK,
} Animation_Name;

typedef enum Step_Rotation
{
    DEFAULT,  // 0 deg
    UP,       // 90 deg
    REVERSED, // 180 deg
    DOWN,     // 270 deg
} Step_Rotation;

typedef enum Sprite_Variant
{
    FRAME,       // sprite, i.e. the standard one
    FULL_SCREEN, // sprite_full_screen
} Sprite_Variant;

// STRUCTURES

typedef struct animation_type
{
    Animation_Name name;
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
    uchar variant;                            // The type of renderer, should be Sprite_Variant.FRAME
    vec2 position;                            // The sprite local position based on its center
    vec2 dimension;                           // The size of the sprite, TODO: decide if this will limit the frames size as well
    vec2f scale;                              // Will see later if I'll implement a proper scale
    float rotation;                           // As with scale above
    Step_Rotation step_rotation;              // A fixed 90° step rotation, because that's just rendering the pixels in a different order
    vec2 flip;                                // To mirror the sprite in x,y direction
    Sprite_State state;                       // Alive, dead, moving, etc.
    char far *frames;                         // Pointer to the sprite sheet frame array, TODO: if this frame array becomes a global -> we don't need this one
    int current_frame;                        // The frame that should be rendered, -1 => should not render anything
    animation_ptr animations[MAX_ANIMATIONS]; // List of all animations the sprite has
    int current_animation;                    // NULL == no animation is playing
} sprite, *sprite_ptr;

// This is a custom sprite that only renders full screen images
typedef struct sprite_full_screen_type
{
    uchar variant;      // The type of sprite, should be Sprite_Variant.FULL_SCREEN, will for example be used to determine which renderer to use
    uchar far *buffer;  // The image data to render, needs to be SCREEN_WIDTH x SCREEN_HEIGHT in size
    uchar far *palette; // If not NULL use this palette, need to point to a RGB_color palette[256];
} sprite_full_screen, *sprite_full_screen_ptr;

// this one should only be used to extract the variant data from a unknown sprite type pointer
typedef struct sprite_variant_type
{
    uchar variant;
} sprite_variant, *sprite_variant_ptr;

// PROTOTYPES

#endif