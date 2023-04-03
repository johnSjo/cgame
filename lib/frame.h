#ifndef FRAME_H
#define FRAME_H

#include <malloc.h>
#include "vec.h"
#include "typedef.h"

// ENUMS

// STRUCTURES

typedef struct frame_type
{
  uchar far *buffer; // The pointer to the image data
  char transparent;  // 0 = opaque, 1 = has some transparent pixels
  vec2 dimension;    // The size of the frame
} frame, *frame_ptr;

// PROTOTYPES
void Free_Frame(frame_ptr frame);

#endif