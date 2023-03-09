#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>

#define VGA256         0x13
#define TEXT_MODE      0x03
#define SCREEN_WIDTH   (unsigned int)320
#define SCREEN_HEIGHT  (unsigned int)200

unsigned char far *video_buffer = (unsigned char far *)0xA0000000L;

void Set_Video_Mode(int mode){
  union REGS inregs,outregs;

  inregs.h.ah = 0;
  inregs.h.al = (unsigned char)mode;

  int86(0x10, &inregs, &outregs);
}

void Fill_Screen(int color){
  _fmemset(video_buffer, (char)color, SCREEN_WIDTH*SCREEN_HEIGHT+1);
}

void Plot_Pixel(int x, int y, char color){
  video_buffer[SCREEN_WIDTH * y + x] = color;
}

void Plot_Pixel_Fast(int x, int y, char color){
  // This assumes that the screen size is fixed at 320x200
  video_buffer[SCREEN_WIDTH * y + x] = color;
}

void main(void){

  Set_Video_Mode(VGA256);

  for(int i = 0; i < 1000; i++)
  Fill_Screen(i + 50);

  while(!kbhit()){}

  Set_Video_Mode(TEXT_MODE);
}