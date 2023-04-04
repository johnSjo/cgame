#include "sprite.h"

// FUNCTIONS

sprite_ptr Init_Sprite(char *id, sprite_sheet_asset_ptr asset)
{
    int i;
    sprite_ptr sprite;

    if (!(sprite = _fmalloc(sizeof(struct sprite_type))))
    {
        printf("\nError, initialize sprite id: %s, failed to allocate memory.", id);
        return NULL;
    };

    sprite->type = SPRITE_FRAME;
    _fstrcpy(sprite->id, id);
    sprite->position.x = 0;
    sprite->position.y = 0;
    sprite->scale.x = 1.0f;
    sprite->scale.y = 1.0f;
    sprite->rotation = 0.0f;
    sprite->step_rotation = DEFAULT;
    sprite->mirror.x = 0;
    sprite->mirror.y = 0;
    sprite->asset = asset;
    sprite->current_frame = -1;
    sprite->current_animation = -1;
    for (i = 0; i < MAX_ANIMATIONS; i++)
    {
        sprite->animations[i] = NULL;
    }

    return sprite;
}

void Render_Sprite(sprite_ptr sprite)
{

    if (sprite->asset->transparent)
        Render_Transparent_Sprite(sprite);
    else
        Render_Opaque_Sprite(sprite);
}

static void Render_Transparent_Sprite(sprite_ptr sprite)
{
    printf("\nRender_Transparent_Sprite not yet implemented");
}

static void Render_Opaque_Sprite(sprite_ptr sprite)
{
    // TODO: this function works but could probably be simplified and optimized

    int i;
    int frame_row_word_size;
    vec2 frame_size;
    vec2 image_size;
    uint offset;
    uint offset_row;
    char frame = sprite->current_frame;
    char frame_col;
    char frame_row;
    char far *frame_row_address, *video_address;
    vec2 position = sprite->position;
    sprite_sheet_asset_ptr asset = sprite->asset;

    frame_size = asset->frame_dimension;
    image_size = asset->sheet_dimension;
    frame_row = frame / asset->number_of_frames.x;
    frame_col = frame % asset->number_of_frames.x;
    frame_row_word_size = frame_size.x >> 1;

    offset = frame_row * frame_size.y * image_size.x + (frame_col * frame_size.x);
    offset_row = image_size.x;

    for (i = 0; i < frame_size.y; i++)
    {
        video_address = video_buffer + (((position.y + i) << 8) + (position.y + i << 6)) + position.x;
        frame_row_address = asset->buffer + offset + (i * offset_row);

        _asm {
            push ds;
            les di, video_address;
            lds si, frame_row_address;
            mov cx, frame_row_word_size;
            cld;
            rep movsw;
            pop ds;
        }
    }
}