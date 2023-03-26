#include <stdarg.h>
#include "cgame.h"

void main()
{
  pcx_image image;

  Set_Video_Mode(VGA256);

  // if (PCX_Load("assets/images/sprite.pcx", &image))
  if (PCX_Load("assets/images/moqmt.pcx", &image))
  // if (PCX_Load("assets/images/test.pcx", &image))
  // if (PCX_Load("assets/images/big.pcx", &image))
  {
    PCX_Enable_Palette(&image);
    PCX_Show_Buffer(&image);
    PCX_Delete(&image);
  }

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