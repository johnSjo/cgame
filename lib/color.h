#ifndef COLOR_H
#define COLOR_H

#include <dos.h>
#include "typedef.h"

#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9

// STRUCTS
typedef struct RGB_color_typ
{
  uchar red;
  uchar green;
  uchar blue;
} RGB_color, *RGB_color_ptr;

// PROTOTYPES
void Set_Palette_Register(int index, RGB_color_ptr color);
void Get_Palette_Register(int index, RGB_color_ptr color);

#endif