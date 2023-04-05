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

void Plot_Pixel_Fast(int x, int y, char color)
{
    // This assumes that the screen size is fixed at 320x200
    video_buffer[((y << 8) + (y << 6)) + x] = color;
}

void Fill_Screen(int color)
{
    _fmemset(video_buffer, (char)color, 64001);

    // _fmemset is about twice as fast, probably because it sets 16bit a time, not sure
    // and the asm code can probably be better, but for now I'll stick to memset
    // _asm {
    //     push ds
    //     les di, video_buffer
    //     mov ax, color
    //     mov cx, 64000
    //     cld
    //     rep stosb
    //     pop ds
    // }
}