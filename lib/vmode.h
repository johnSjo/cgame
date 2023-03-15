#ifndef VMODE_H
#define VMODE_H

#include <stdio.h>
#include <DOS.H>
#include <CONIO.H>
#include "typedef.h"

#define VGA256 0x13
#define TEXT_MODE 0x03
#define SCREEN_WIDTH (unsigned int)320
#define SCREEN_HEIGHT (unsigned int)200

// GLOBALS
extern uchar far *video_buffer;

// PROTOTYPES
void Set_Video_Mode(int mode);

#endif