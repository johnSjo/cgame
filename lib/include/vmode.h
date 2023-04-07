#ifndef VMODE_H
#define VMODE_H

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include "typedef.h"

#define SET_MODE 0x00
#define VIDEO_INTERRUPT 0x10
#define VGA256 0x13
#define TEXT_MODE 0x03
#define SCREEN_WIDTH (unsigned int)320
#define SCREEN_HEIGHT (unsigned int)200
#define INPUT_STATUS 0x3DA
#define VRETRACE_BIT 0x08

// GLOBALS
extern uchar far *video_buffer;

// PROTOTYPES
void Set_Video_Mode(int mode);
void wait_for_retrace(void);
void Plot_Pixel_Fast(int x, int y, char color);
void Fill_Screen(uchar color);

#endif