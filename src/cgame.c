#include <stdarg.h>
#include <string.h>
#include "cgame.h"

void main()
{
  pcx_image image;
  vec2 offset = {20, 20};
  vec2 size = {140, 20};
  uchar far *section;
  int i;

  Set_Video_Mode(VGA256);

  // if (PCX_Load("assets/images/sprite.pcx", &image))
  if (PCX_Load("assets/images/moqmt.pcx", &image))
  // if (PCX_Load("assets/images/tanks.pcx", &image))
  // if (PCX_Load("assets/images/married.pcx", &image))
  // if (PCX_Load("assets/images/outpost.pcx", &image))
  // if (PCX_Load("assets/images/test.pcx", &image))
  // if (PCX_Load("assets/images/big.pcx", &image))
  {
    // PCX_Enable_Palette(&image);
    PCX_Show_Buffer(&image);
    PCX_Delete(&image);
  }

  section = PCX_Create_Section(&image, offset, size);

  printf("\n");
  printf("\nsection size : %u", sizeof(section));
  printf("\nsection   &p : %p", &section);
  printf("\nsection    p : %p", section);
  printf("\nsection    u : %u", section);
  printf("\nsection    * : %u", *section);

  printf("\n");
  for (i = 0; i < 10; i++)
  {
    printf("| %u |", section[i]);
  }
  printf("\n");
  printf("\n1722:0004    : %u", (uchar far *)(0x171D0005));
  printf("\n");

  section[2] = 5;

  // _fmemset((uchar far *)section, 3, 10);

  for (i = 0; i < 10; i++)
  {
    printf("| %u |", section[i]);
  }

  printf("\nfree");
  _ffree(section);

  // printf("\n\nsection 0    : %u", section[0]);
  // printf("\nsection 1    : %u", section[1]);
  // printf("\nsection 2    : %u", section[2]);
  // printf("\nsection 3    : %u", section[3]);

  // printf("\nsection      : %u", (char far *)(section + 0));
  // printf("\nsection      : %u", (char far *)(section + 1));
  // printf("\nsection      : %u", (char far *)(section + 2));
  // printf("\nsection      : %u", (char far *)(section + 3));

  // printf("\nChar      : %u", sizeof(char));
  // printf("\nInt       : %u", sizeof(int));
  // printf("\nLong      : %u", sizeof(long));
  // printf("\nFloat     : %u", sizeof(float));
  // printf("\nDouble    : %u", sizeof(double));
  // printf("\nDouble L  : %u", sizeof(long double));

#ifdef PROD
  printf("\nNow we're in production");
#endif

  while (!kbhit())
  {
  }

  Set_Video_Mode(TEXT_MODE);
}