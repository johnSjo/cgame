#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define VGA256 0x13
#define TEXT_MODE 0x03
#define SCREEN_WIDTH (unsigned int)320
#define SCREEN_HEIGHT (unsigned int)200

#define PALETTE_MASK 0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA 0x3c9

// TYPEDEF
typedef unsigned char uchar;

// GLOBALS
uchar far *video_buffer = (uchar far *)0xA0000000L;
uchar far *rom_char_set = (char far *)0xf000fa6EL;

// STRUCTS
typedef struct RGB_color_typ
{
  uchar red;
  uchar green;
  uchar blue;
} RGB_color, *RGB_color_ptr;

// FUNCTIONS
void Set_Video_Mode(int mode)
{
  union REGS inregs, outregs;

  inregs.h.ah = 0;
  inregs.h.al = (uchar)mode;

  int86(0x10, &inregs, &outregs);
}

void Fill_Screen(int color)
{
  _fmemset(video_buffer, (char)color, SCREEN_WIDTH * SCREEN_HEIGHT + 1);
}

void Plot_Pixel(int x, int y, char color)
{
  video_buffer[SCREEN_WIDTH * y + x] = color;
}

void Plot_Pixel_Fast(int x, int y, char color)
{
  // This assumes that the screen size is fixed at 320x200
  video_buffer[((y << 8) + (y << 6)) + x] = color;
}

void Draw_Horizontal_Line(int x, int y, int length, char color)
{
  int i;
  for (i = x; i < x + length; i++)
    Plot_Pixel_Fast(i, y, color);
}

void Draw_Vertical_Line(int x, int y, int length, char color)
{
  int i;
  for (i = y; i < y + length; i++)
    Plot_Pixel_Fast(x, i, color);
}

void Draw_Horizontal_Line_Memset(int start_x, int end_x, int y, unsigned int color)
{
  if (end_x > start_x)
  {
    _fmemset((char far *)(video_buffer + ((y << 8) + (y << 6)) + start_x), color, end_x - start_x + 1);
  }
}

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

void Print_Char(
    int pos_x,
    int pos_y,
    char character,
    int color,
    int background_color)
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

void main(void)
{
  // char boo[6] = {'h','e','l','l','o','\0'};
  // char boo[] = "Foo";
  //  unsigned int boo = (1000 << 6) + 768;
  //  int i,w,h;
  //  clock_t startClock = clock();
  //  double deltaClock;
  //  double deltaSec;
  //  int foo = 0x0cff>>16;
  RGB_color color;
  int foo[100];
  int doo = 12;
  int *goo = malloc(2000);
  int poo = 2;

  // memset(goo, 1, 2000);
  Set_Video_Mode(VGA256);

  // for(i = 0; i < 1000; i++)
  //   Fill_Screen(i + 50);

  Fill_Screen(230);

  Draw_Horizontal_Line(0, 50, 9 << 3, 100);
  Draw_Vertical_Line(9 << 3, 0, 6 << 3, 110);
  color.red = 63;
  color.green = 0;
  color.blue = 0;
  Set_Palette_Register(100, (RGB_color_ptr)&color);
  Draw_Horizontal_Line_Memset(10, 210, 100, 100);
  Draw_Vertical_Line(10, 50, 50, 110);

  // for(h = 0; h < SCREEN_HEIGHT; h++){
  //   for(w = 0; w < SCREEN_WIDTH; w++){
  //       Plot_Pixel(w, h, 100);
  //   }
  // }

  Plot_Pixel(150, 150, 220);

  printf("red: 0x%x\n", color.red);
  printf("green: 0x%x\n", color.green);
  printf("blue: 0x%x\n", color.blue);

  Get_Palette_Register(100, (RGB_color_ptr)&color);

  //   while(!kbhit()){}

  //   char boo[6] = "hello";

  // t = clock() - t;
  // time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time

  // printf("%u\n", boo);
  // printf("%u", sizeof(boo));
  // printf("%f\n", time_taken);
  // printf("%u\n", sizeof(time_taken));
  // printf("%u\n", sizeof(CLOCKS_PER_SEC));
  // printf("%f\n", CLOCKS_PER_SEC);

  // deltaClock = clock() - startClock;
  // deltaSec = (double)deltaClock / CLOCKS_PER_SEC;
  // printf("DeltaClock: %f\n", (double)deltaClock);
  // printf("DeltaSec: %f\n", deltaSec);
  // printf("foo: %x\n", foo);

  printf("red: 0x%x\n", color.red);
  printf("green: 0x%x\n", color.green);
  printf("blue: 0x%x\n", color.blue);
  gotoxy(2, 10);
  printf("width: %u", 320 >> 3);
  printf(" height: %u", 200 >> 3);

  Print_Char(20, 120, 'H', 100, -1);
  Print_String(20, 130, "Hello!", 100, -1);

  printf("\nsize: %u", sizeof(foo));
  printf("\nadress: %p", &foo);
  printf("\nsize: %u", sizeof(doo));
  printf("\nadress: %p", &doo);
  printf("\nsize: %u", sizeof(goo));
  printf("\nadress: %p", &goo);
  printf("\ngoo: %p", goo);
  printf("\nsize: %u", sizeof(poo));
  printf("\nadress: %p", &poo);

  while (!kbhit())
  {
  }

  Set_Video_Mode(TEXT_MODE);
}