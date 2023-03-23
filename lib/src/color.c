#include "color.h"

// FUNCTIONS
void Set_Palette_Register(int index, RGB_color_ptr color)
{
  outportb(PALETTE_MASK, 0xff);

  outportb(PALETTE_REGISTER_WR, index);

  outportb(PALETTE_DATA, color->red);
  outportb(PALETTE_DATA, color->green);
  outportb(PALETTE_DATA, color->blue);
}

void Get_Palette_Register(int index, RGB_color_ptr color)
{
  outportb(PALETTE_MASK, 0xff);

  outportb(PALETTE_REGISTER_RD, index);

  color->red = inportb(PALETTE_DATA);
  color->green = inportb(PALETTE_DATA);
  color->blue = inportb(PALETTE_DATA);
}