#include "text.h"

// GLOBALS
uchar far *rom_char_set = (uchar far *)0xf000fa6EL;

// FUNCTIONS
void Print_Char(int pos_x, int pos_y, char character, int color, int background_color)
{
  int offset, x, y;
  char far *work_char;
  uchar bit_mask = 0x80;

  work_char = rom_char_set + character * 8;
  offset = (pos_y << 8) + (pos_y << 6) + pos_x;

  for (y = 0; y < 8; y++)
  {
    bit_mask = 0x80;

    for (x = 0; x < 8; x++)
    {
      if (*work_char & bit_mask)
      {
        video_buffer[offset + x] = color;
      }
      else if (background_color >= 0)
      {
        video_buffer[offset + x] = background_color;
      }

      bit_mask = bit_mask >> 1;
    }

    offset += SCREEN_WIDTH;
    work_char++;
  }
}

void Print_String(
    int pos_x,
    int pos_y,
    char *string,
    int color,
    int background_color)
{
  int i = 0;

  while (string[i] != 0)
  {
    Print_Char(pos_x + (i << 3), pos_y, string[i], color, background_color);
    i++;
  }
}