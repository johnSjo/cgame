#include "vmode.h"
#include "typedef.h"

void main()
{
  uint boo = 34;

  Set_Video_Mode(VGA256);

  printf("It's alive!!! %u", boo);
  Print_String(5, 10, "Hello", 13, 0);

  while (!kbhit())
  {
  }

  Set_Video_Mode(TEXT_MODE);
}