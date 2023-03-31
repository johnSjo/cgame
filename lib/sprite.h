#ifndef SPRITE_H
#define SPRITE_H

#include "vec.h"
#include "typedef.h"

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

// STRUCTURES

typedef struct animation_type
{
    Animation_Name name;
    uchar frames[MAX_ANIMATION_FRAMES]; // Array of indexes to the sprite frames
    int repeat;                         // -1 = infinite loop, 0 = play once, 1..max = repeat n times
    int current_repeat;
    char jojo;
    char jojo_direction;
    float frame_time;
    float current_time;
    float duration;
} animation, *animation_ptr;

typedef struct sprite_type
{
    vec2 position;
    vec2 dimension;
    vec2f scale;    // Will see later if I'll implement a proper scale
    float rotation; // As with scale above
    // maybe implement a fixed 90° step rotation, because that's just rendering the pixels in a different order
    vec2 flip;                           // To mirror the sprite in x,y direction
    Sprite_State state;                  // Alive, dead, moving, etc.
    char far *frames[MAX_SPRITE_FRAMES]; // Pointers to all available
    int current_frame;
    animation animations[MAX_ANIMATIONS]; // List of all animations the sprite has
    int playing_animation;
} sprite, *sprite_ptr;

// PROTOTYPES

#endif