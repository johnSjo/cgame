#include "vmode.h"
#include "typedef.h"
#include "text.h"
#include "color.h"
#include "pcx.h"

void main()
{
  pcx_image image;

  Set_Video_Mode(VGA256);

  if (PCX_Load("assets/images/moqmt.pcx", &image))
  // if (PCX_Load("assets/images/test.pcx", &image))
  // if (PCX_Load("assets/images/big.pcx", &image))
  {
    PCX_Enable_Palette(&image);
    PCX_Show_Buffer(&image);
    PCX_Delete(&image);
  }

#ifdef PROD
  printf("\nNow we're in production");
#endif

  while (!kbhit())
  {
  }

  Set_Video_Mode(TEXT_MODE);
}