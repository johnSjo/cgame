#ifndef PCX_H
#define PCX_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "vmode.h"
#include "color.h"
#include "vec.h"

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

typedef struct pcx_image_type
{
    pcx_header header;
    RGB_color palette[256];
    char far *buffer;
} pcx_image, *pcx_image_ptr;

// PROTOTYPES

int PCX_Load(char *filename, pcx_image_ptr image);
void PCX_Allocate_Buffer(pcx_image_ptr image, uint width, uint height);
void PCX_Enable_Palette(pcx_image_ptr image);
// For displaying the whole image
void PCX_Show_Buffer(pcx_image_ptr image);
void PCX_Delete(pcx_image_ptr image);
unsigned char far *PCX_Create_Section(pcx_image_ptr image, vec2 offset, vec2 size);

#endif