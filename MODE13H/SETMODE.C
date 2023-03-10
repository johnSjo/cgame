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
  video_buffer[((y << 8) + (y << 6)) + x] = color;
}

void Draw_Horizontal_Line(int x, int y, int length, char color){
  int i;
  for(i = x; i < x + length; i++)
    Plot_Pixel_Fast(i, y, color);
}

void main(void){
  //char boo[6] = {'h','e','l','l','o','\0'};
  //char boo[] = "Foo";
  unsigned int boo = (1000 << 6) + 768;
  int i,w,h;

  Set_Video_Mode(VGA256);

  // for(i = 0; i < 1000; i++)
  //   Fill_Screen(i + 50);

  Fill_Screen(230);

  Draw_Horizontal_Line(10, 50, 300, 100);

  for(h = 0; h < SCREEN_HEIGHT; h++){
    for(w = 0; w < SCREEN_WIDTH; w++){
        Plot_Pixel(w, h, 100);
    }
  }

  Plot_Pixel(150, 150, 220);

//   while(!kbhit()){}



//   char boo[6] = "hello";

  //printf("%u\n", boo);
  //printf("%u", sizeof(boo));

  while(!kbhit()){}
  Set_Video_Mode(TEXT_MODE);
}