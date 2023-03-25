#include <malloc.h>
#include <stdio.h>
#include "vmode.h"
#include "typedef.h"
#include "text.h"
#include "color.h"

// STRUCTURES

typedef struct pcx_header_type
{
  char manufacture;
  char version;
  char encoding; // 1 = RLE encoding, 0 = uncompressed
  char bits_per_pixel;
  int x, y;
  int width, height;
  int horizontal_resolution;
  int vertical_resolution;
  char ega_palette[48];
  char reserved;
  char num_color_planes;
  int bytes_per_line;
  int palette_type;
  char padding[58];
} pcx_header, *pcx_header_ptr;

typedef struct pcx_picture_type
{
  pcx_header header;
  RGB_color palette[256];
  char far *buffer;
} pcx_picture, *pcx_picture_ptr;

// Pro

int PCX_Load(char *filename, pcx_picture_ptr image);
void PCX_Enable_Palette(pcx_picture_ptr image);
void PCX_Delete(pcx_picture_ptr image);

// For displaying the whole image
void PCX_Show_Buffer(pcx_picture_ptr image);

// Func
void PCX_Init_Buffer(pcx_picture_ptr image, uint width, uint height)
{
  uint image_width = width ? width : SCREEN_WIDTH;
  uint image_height = height ? height : SCREEN_HEIGHT;

  if (!(image->buffer = (char far *)_fmalloc(image_width * image_height + 1)))
    printf("\nCouldn't allocate image buffer");
}

int PCX_Load(char *filename, pcx_picture_ptr image)
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

  PCX_Init_Buffer(image, width, height);

  while (count <= width * height)
  {
    data = (uchar)getc(file_ptr);

    if (data < 192)
    {
      image->buffer[count++] = data;
      continue;
    }

    if (data > 255)
      printf("%u", data);

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

void PCX_Enable_Palette(pcx_picture_ptr image)
{
  int index;

  for (index = 0; index < 256; index++)
  {
    Set_Palette_Register(index, (RGB_color_ptr)&image->palette[index]);
  }
}

void PCX_Delete(pcx_picture_ptr image)
{
  _ffree(image->buffer);
}

void PCX_Show_Buffer(pcx_picture_ptr image)
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

void main()
{
  pcx_picture image;

  Set_Video_Mode(VGA256);

  if (PCX_Load("assets/images/moqmt.pcx", &image))
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