#include "vmode.h"

// GLOBALS
uchar far *video_buffer = (uchar far *)0xA0000000L;

// FUNCTIONS
void Set_Video_Mode(int mode)
{
  union REGS inregs, outregs;

  inregs.h.ah = SET_MODE;
  inregs.h.al = (uchar)mode;

  int86(VIDEO_INTERRUPT, &inregs, &outregs);
}
