#include "pcx.h"

// FUNCTIONS
void PCX_Allocate_Buffer(pcx_image_ptr image, uint width, uint height)
{
    uint image_width = width ? width : SCREEN_WIDTH;
    uint image_height = height ? height : SCREEN_HEIGHT;

    if (!(image->buffer = (char far *)_fmalloc(image_width * image_height + 1)))
        printf("\nCouldn't allocate image buffer");
}

int PCX_Load(char *filename, pcx_image_ptr image)
{
    int pcx_header_size = sizeof(image->header);
    char far *header_buffer = (char far *)&(image->header);
    pcx_header_ptr header = (pcx_header_ptr)header_buffer;
    FILE *file_ptr;
    int number_of_bytes, index;
    uint width, height;
    long count = 0;
    uchar data;

    file_ptr = fopen(filename, "rb");

    for (index = 0; index < pcx_header_size; index++)
    {
        header_buffer[index] = (char)getc(file_ptr);

        // Alternatives to use the header ptr directly (but the header_buffer is a bit cleaner imo.)
        // *((char *)header + index) = (char)getc(file_ptr);
        // ((char *)header)[index] = (char)getc(file_ptr);
    }

#ifdef DEV
    if (((long)header->width * header->height) > 65000)
    {
        printf("\nPCX_Load: large (> ~320x200) image sizes is currently not suported.");
        return 0;
    }
#endif

    width = (header->width + 1);
    height = (header->height + 1);

    PCX_Allocate_Buffer(image, width, height);

    while (count <= width * height)
    {
        data = (uchar)getc(file_ptr);

        if (data < 192)
        {
            image->buffer[count++] = data;
            continue;
        }

        // is a RLE run
        number_of_bytes = data - 192;
        data = (uchar)getc(file_ptr);

        while (number_of_bytes-- > 0)
        {
            image->buffer[count++] = data;
        }
    }

    fseek(file_ptr, -768L, SEEK_END);

    for (index = 0; index < 256; index++)
    {
        image->palette[index].red = (uchar)(getc(file_ptr) >> 2);
        image->palette[index].green = (uchar)(getc(file_ptr) >> 2);
        image->palette[index].blue = (uchar)(getc(file_ptr) >> 2);
    }

    fclose(file_ptr);

    return 1;
}

void PCX_Enable_Palette(pcx_image_ptr image)
{
    int index;

    for (index = 0; index < 256; index++)
    {
        Set_Palette_Register(index, (RGB_color_ptr)&image->palette[index]);
    }
}

void PCX_Delete(pcx_image_ptr image)
{
    _ffree(image->buffer);
}

void PCX_Show_Buffer(pcx_image_ptr image)
{
    // NOTE: since the video_buffer is layed out in 320x200, using an image with
    // a different width would not display properly.
    // And a height more than 200 would also cause issues.
    int width = image->header.width + 1;
    int height = image->header.height + 1;
    int size = width * height / 2;
    char far *data = image->buffer;

    _asm {
        push ds;
        les di, video_buffer;
        lds si, data;
        mov cx, size;
        cld;
        rep movsw;
        pop ds;
    }
}

unsigned char far *PCX_Create_Section(pcx_image_ptr image, vec2 offset, vec2 size)
{
    uint buffer_size = size.x * size.y;
    uchar far *buffer;
    pcx_header_ptr header = &image->header;
    uint image_width = header->width + 1;
    uint image_height = header->height + 1;
    int x, y;

    // Check if section is inside image
    if (((offset.x + size.x) > image_width) || ((offset.y + size.y) > image_height))
    {
        printf("\nPCX_Create_Section: section is outside of the image.");
        return NULL;
    }

    buffer = (uchar far *)_fmalloc(buffer_size);
    // _fmemset(buffer, 3, buffer_size);
    printf("\nTemp: %u", image_width);
    // printf("\nTemp: %p", buffer);

    for (y = 0; y < size.y; y++)
    {
        _fmemcpy(
            (buffer + (y * size.x)),
            (image->buffer + (((offset.y + y) * image_width) + offset.x)),
            size.x);
    }

    return buffer;
}