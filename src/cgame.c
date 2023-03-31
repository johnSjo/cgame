#include <stdarg.h>
#include <string.h>
#include "cgame.h"

void main()
{
    pcx_image image;
    vec2 offset = {150, 60};
    vec2 size = {40, 40};
    vec2 position = {200, 120};
    uchar far *section, *video_address, *section_address;
    int i;
    int buffer_size;

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

    buffer_size = size.x >> 1;
    for (i = 0; i < size.y; i++)
    {
        video_address = video_buffer + (((position.y + i) << 8) + (position.y + i << 6)) + position.x;
        section_address = section + (i * size.x);

        _asm {
            push ds;
            les di, video_address;
            lds si, section_address;
            mov cx, buffer_size;
            cld;
            rep movsw;
            pop ds;
        }
    }

    printf("\nfree");
    _ffree(section);

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