#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <malloc.h>

#define VGA256 0x13
#define TEXT_MODE 0x03
#define SCREEN_WIDTH (unsigned int)320
#define SCREEN_HEIGHT (unsigned int)200

#define NUM_STARS 175
#define PLANE_1 1
#define PLANE_2 2
#define PLANE_3 3

// PROTOTYPES
void Set_Video_Mode(int mode);

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

void Plot_Pixel_Fast(int x, int y, char color);

void Delay(int clicks);

void Init_Stars(void);

// TYPEDEF
typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct star_type
{
  int x, y;
  int plane;
  int color;
} star, *star_ptr;

// GLOBALS
uchar far *video_buffer = (uchar far *)0xA0000000L;
uchar far *rom_char_set = (uchar far *)0xf000fa6EL;
uint far *clock = (uint far *)0x0000046cl;

int star_first = 1;
star stars[NUM_STARS];
int velocity_1 = 2;
int velocity_2 = 4;
int velocity_3 = 6;

// FUNCTIONS
void Set_Video_Mode(int mode)
{
  union REGS inregs, outregs;

  inregs.h.ah = 0;
  inregs.h.al = (uchar)mode;

  int86(0x10, &inregs, &outregs);
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

void Plot_Pixel_Fast(int x, int y, char color)
{
  // This assumes that the screen size is fixed at 320x200
  video_buffer[((y << 8) + (y << 6)) + x] = color;
}

void Delay(int clicks)
{
  uint now = *clock;

  while (abs(*clock - now) < clicks)
  {
  }
}

void Init_Stars(void)
{
  int i;

  for (i = 0; i < NUM_STARS; i++)
  {
    stars[i].x = rand() % SCREEN_WIDTH;
    stars[i].y = rand() % SCREEN_HEIGHT;

    switch (rand() % 3)
    {
    case 0:
      stars[i].plane = PLANE_1;
      stars[i].color = 8;
      break;
    case 1:
      stars[i].plane = PLANE_2;
      stars[i].color = 7;
      break;
    case 2:
      stars[i].plane = PLANE_3;
      stars[i].color = 15;
      break;

    default:
      break;
    }
  }
}

void main(void)
{
  int done = 1, index;
  star_ptr star;
  int blocks = 10;
  uchar far *boo[10];

  Set_Video_Mode(VGA256);

  Init_Stars();

  while (!done)
  {
    if (kbhit())
    {
      switch (getch())
      {
      case '-':
        velocity_1 -= 1;
        velocity_2 -= 2;
        velocity_3 -= 3;
        break;
      case '=':
        velocity_1 += 1;
        velocity_2 += 2;
        velocity_3 += 3;
        break;
      case 'q':
        done = 1;
        break;

      default:
        break;
      }
    }

    for (index = 0; index < NUM_STARS; index++)
    {
      star = &stars[index];
      Plot_Pixel_Fast(star->x, star->y, 0);

      switch (star->plane)
      {
      case PLANE_1:
        star->x += velocity_1;
        break;
      case PLANE_2:
        star->x += velocity_2;
        break;
      case PLANE_3:
        star->x += velocity_3;
        break;

      default:
        break;
      }

      if (star->x >= SCREEN_WIDTH)
        star->x -= SCREEN_WIDTH;
      else if (star->x < 0)
        star->x += SCREEN_WIDTH;

      Plot_Pixel_Fast(star->x, star->y, star->color);
    }

    Delay(1);
  }

  // printf("\nBuffer P   : %p", &boo);
  // printf("\nBuffer S   : %u", sizeof(boo));
  // printf("\nBuffer     : %u", boo);
  // printf("\nIndex      : %p", &index);

  for (index = 0; index < blocks; index++)
  {
    boo[index] = (uchar far *)_fmalloc(64000);

    if (boo[index] == NULL)
      printf("\nOUT OF MEM");
    else
    {
      // printf("\n---------");
      // printf("\nBuffer P   : %p", &boo);
      // printf("\nBuffer S   : %u", sizeof(boo));
      // printf("\nBuffer     : %u", boo);
      // printf("\nIndex      : %p", &index);
      printf("\nBoo      : %p", &boo[index]);
    }
  }

  while (!kbhit())
  {
  }

  Set_Video_Mode(TEXT_MODE);
}
