#ifndef TEXT_H
#define TEXT_H

#include "vmode.h"
#include "typedef.h"

// GLOBALS
extern uchar far *rom_char_set;

// PROTOTYPES
void Print_Char(
    int pos_x,
    int pos_y,
    char character,
    int color,
    int background_color);

void Print_String(
    int pos_x,
    int pos_y,
    char *string,
    int color,
    int background_color);

#endif