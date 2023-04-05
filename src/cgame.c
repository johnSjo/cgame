#include "cgame.h"

#define N_SPRITES 260

// int main(int argc, char *argv[])
int main(void)
{
    long i, j, boo;
    vec2 anchor = {160, 100}, point = {160, 10};
    vec2 point_old = point;
    vec2 pixel;
    double angle;
    int sprite_index;
    float n_points = 5;
    int rotation = 0;
    clock_t start_time, end_time;
    float frame_time;
    char far *video_address = (video_buffer + 3200);

    sprite_sheet_asset_ptr asset;
    sprite_ptr sprite;
    sprite_ptr sprites[N_SPRITES];

    Set_Video_Mode(VGA256);

    // for (i = 0; i <= n_points; i++)
    // {
    //     angle = ((i / n_points) * 360) * (M_PI / 180.0);
    //     pixel = Rotate_Point(point, anchor, angle);
    //     Render_Line(point_old, pixel, 45);
    //     point_old = pixel;
    //     // Plot_Pixel_Fast(pixel.x, pixel.y, 45);
    //     // printf("\n%f | ", angle);
    // }

    // if (Init_Assets_Store())
    // {
    //     Set_Video_Mode(TEXT_MODE);
    //     return 1;
    // }

    // asset = (sprite_sheet_asset_ptr)Get_Asset("tanks");

    // for (i = 0; i < N_SPRITES; i++)
    // {
    //     sprites[i] = Init_Sprite("player", asset);
    //     sprites[i]->position.x = (i % 20) * 16;
    //     sprites[i]->position.y = (i / 20) * 16;
    //     sprites[i]->current_frame = rand() % 32;
    // }

#ifdef PROD
    printf("\nNow we're in production");
#endif

    while (!kbhit())
    {

        // for (i = 0; i <= n_points; i++)
        // {
        //     angle = deg_to_rad((i / n_points) * 360 + rotation);
        //     pixel = Rotate_Point(point, anchor, angle);
        //     Render_Line(point_old, pixel, 45);
        //     point_old = pixel;
        //     // Plot_Pixel_Fast(pixel.x, pixel.y, 45);
        //     // printf("\n%f | ", angle);
        // }
        // for (i = 0; i < N_SPRITES; i++)
        // {
        //     sprites[i]->current_frame = (sprites[i]->current_frame + 1) % 32;
        //     Render_Sprite(sprites[i]);
        // }

        for (j = 0; j < 500; j++)
        {
            boo = j / 3.14;
        }

        _fmemset((video_buffer + 3200), 0, 60000);
        // rotation = (rotation++) % 360;
        // point.y = (sin(deg_to_rad(rotation)) * 25) + 50;

        // Update game state and render the frame

        end_time = clock();
        frame_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
        // printf("\033[%d;%dHTime: %ld | %ld", 2, 0, start_time, end_time);
        start_time = clock();
        printf("\033[%d;%dHHello, world! %u | %f", 0, 0, point.y, frame_time);
        // printf("\033[%d;%dHTime: %f", 3, 0, CLOCKS_PER_SEC);
        // printf("\033[%d;%dHTime: %u", 4, 0, rotation);
    }

    // Free_Assets_Store();

    Set_Video_Mode(TEXT_MODE);

    return 0;
}
// // // printf with position
// // // printf("\033[%d;%dHHello, world! %u", 10, 10, i);
