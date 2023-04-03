#include <stdarg.h>
#include <string.h>
#include "cgame.h"

// int main(int argc, char *argv[])
int main(void)
{
    long i;
    char text[32];

    Set_Video_Mode(VGA256);

    if (Init_Assets_Store())
    {
        Set_Video_Mode(TEXT_MODE);
        return 1;
    }

#ifdef PROD
    printf("\nNow we're in production");
#endif

    while (!kbhit())
    {
    }

    Free_Assets_Store();

    Set_Video_Mode(TEXT_MODE);

    return 0;
}
// printf with position
// printf("\033[%d;%dHHello, world! %u", 10, 10, i);

// buffer_size = size.x >> 1;
// printf("\nbuffer_size: %u", buffer_size);
// for (frame_index = 0; frame_index < 16; frame_index++)
// {
//     section = tank.frames[frame_index];
//     printf("\nsection: %p", section);
//     for (i = 0; i < size.y; i++)
//     {
//         video_address = video_buffer + (((position.y + i) << 8) + (position.y + i << 6)) + position.x;
//         section_address = section + (i * size.x);

//         _asm {
//             push ds;
//             les di, video_address;
//             lds si, section_address;
//             mov cx, buffer_size;
//             cld;
//             rep movsw;
//             pop ds;
//         }
//     }

//     // position.y += 16;
//     position.x += 16;
// }

// section = tank.frames[frame_index];
// buffer_size = size.x >> 1;
// for (i = 0; i < size.y; i++)
// {
//     video_address = video_buffer + (((position.y + i) << 8) + (position.y + i << 6)) + position.x;
//     section_address = section + (i * size.x);

//     _asm {
//     push ds;
//     les di, video_address;
//     lds si, section_address;
//     mov cx, buffer_size;
//     cld;
//     rep movsw;
//     pop ds;
//     }
// }

// frame_index++;
// if (frame_index > 15)
// {
//     frame_index = 0;
// }

// for (i = 0; i < 40000; i++)
// {
//     delay = i / 3.14;
// }

// position.y += 1;
// position.x += 1;

// for (i = 0; i < 16; i++)
// {
//     _ffree(tank.frames[i]);
// }

// PCX_Delete(&image);

// // if (PCX_Load("assets/images/sprite.pcx", &image))
// // if (PCX_Load("assets/images/moqmt.pcx", &image))
// if (PCX_Load("assets/images/tanks.pcx", &image))
// // if (PCX_Load("assets/images/married.pcx", &image))
// // if (PCX_Load("assets/images/outpost.pcx", &image))
// // if (PCX_Load("assets/images/test.pcx", &image))
// // if (PCX_Load("assets/images/big.pcx", &image))
// {
//     PCX_Enable_Palette(&image);
//     PCX_Show_Buffer(&image);
// }

// for (i = 0; i < 16; i++)
// {
//     offset.x = i * 16;
//     tank.frames[i] = PCX_Create_Section(&image, offset, size);
// }
// section = PCX_Create_Section(&image, offset, size);

// printf("\n");
// printf("\nsection size : %u", sizeof(bitmap_asset));
// Print_Char(20, 120, 'H', 100, -1);
// Print_String(21, 41, "section size : 900", 118, -1);
// Print_String(20, 40, "section size : 900", 90, -1);
// asset = Get_Asset("first asset");

// printf("\nasset    : %p", asset);
// printf("\nasset id : %s", asset->id);
// frame = asset->frame;
// printf("\nasset x  : %u", frame->dimension.x);
// // printf("\nasset x  : %u", asset->frame->dimension.x);
// printf("\nasset y  : %u", ((frame_ptr)asset->frame)->dimension.y);

// printf("\nsection   &p : %p", &section);
// printf("\nsection    p : %p", section);
// printf("\nsection    u : %u", section);
// printf("\nsection    * : %u", *section);

// printf("\n");
// for (i = 0; i < 10; i++)
// {
//     printf("| %u |", section[i]);
// }
// printf("\n");
// printf("\n1722:0004    : %u", (uchar far *)(0x171D0005));
// printf("\n");

// _fmemset((uchar far *)section, 3, 10);

// for (i = 0; i < 10; i++)
// {
//     printf("| %u |", section[i]);
// }

// section = tank.frames[10];
// buffer_size = size.x >> 1;
// for (i = 0; i < size.y; i++)
// {
//     video_address = video_buffer + (((position.y + i) << 8) + (position.y + i << 6)) + position.x;
//     section_address = section + (i * size.x);

//     // printf("\ni: %p | %p", section_address, video_address);
//     _asm {
//         push ds;
//         les di, video_address;
//         lds si, section_address;
//         mov cx, buffer_size;
//         cld;
//         rep movsw;
//         pop ds;
//     }
// }

// printf("\nfree");
// _ffree(section);

// printf("\nChar      : %u", sizeof(char));
// printf("\nInt       : %u", sizeof(int));
// printf("\nLong      : %u", sizeof(long));
// printf("\nFloat     : %u", sizeof(float));
// printf("\nDouble    : %u", sizeof(double));
// printf("\nDouble L  : %u", sizeof(long double));
