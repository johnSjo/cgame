#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "cgame.h"

#define N_SPRITES 260

// int main(int argc, char *argv[])
int main(void)
{
    long i, j, boo;
    int sprite_index;

    sprite_sheet_asset_ptr asset;
    sprite_ptr sprite;
    sprite_ptr sprites[N_SPRITES];

    Set_Video_Mode(VGA256);

    if (Init_Assets_Store())
    {
        Set_Video_Mode(TEXT_MODE);
        return 1;
    }

    asset = (sprite_sheet_asset_ptr)Get_Asset("tanks");

    for (i = 0; i < N_SPRITES; i++)
    {
        sprites[i] = Init_Sprite("player", asset);
        sprites[i]->position.x = (i % 20) * 16;
        sprites[i]->position.y = (i / 20) * 16;
        sprites[i]->current_frame = rand() % 32;
    }

#ifdef PROD
    printf("\nNow we're in production");
#endif

    while (!kbhit())
    {
        for (i = 0; i < N_SPRITES; i++)
        {
            sprites[i]->current_frame = (sprites[i]->current_frame + 1) % 32;
            Render_Sprite(sprites[i]);
        }

        for (j = 0; j < 10000; j++)
        {
            boo = j / 3.14;
        }
    }

    Free_Assets_Store();

    Set_Video_Mode(TEXT_MODE);

    return 0;
}
// printf with position
// printf("\033[%d;%dHHello, world! %u", 10, 10, i);
