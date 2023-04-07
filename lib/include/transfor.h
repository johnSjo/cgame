#ifndef TRANSFORM_H
#define TRANSFORM_H

// STRUCTURES

typedef struct vec2_type
{
    int x, y;
} vec2, *vec2_ptr;

typedef struct vec2_float_type
{
    float x, y;
} vec2f, *vec2f_ptr;

typedef struct transform_type
{
    vec2f position;
    vec2f scale;
    float rotation;
} transform, *transform_ptr;

#endif