#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "typedef.h"
#include "color.h"
#include "pcx.h"
#include "vec.h"
#include "frame.h"

// ENUMS

typedef enum Asset_Variant
{
  BITMAP,
  IMAGE,
  PALETTE
} Asset_Variant;

// STRUCTS
typedef struct bitmap_config_type
{
  char id[32];
  char path[128];
  vec2 dimension;
} bitmap_config, *bitmap_config_ptr;

typedef struct bitmap_asset_type
{
  char far *id;
  Asset_Variant variant;
  uchar number_of_frames;
  frame_ptr far **frames;
} bitmap_asset, *bitmap_asset_ptr;

typedef struct image_asset_type
{
  char far *id;
  Asset_Variant variant;
  frame_ptr far *frame;
} image_asset, *image_asset_ptr;

typedef struct palette_asset_type
{
  char far *id;
  Asset_Variant variant;
  RGB_color far *palette;
} palette_asset, *palette_asset_ptr;

typedef struct asset_type
{
  char far *id;
  Asset_Variant variant;
} asset, *asset_ptr;

// PROTOTYPES
asset_ptr Get_Asset(char *id);
int Init_Assets_Store(void);
void Free_Assets_Store(void);

// INTERNALS
static int Read_Config_File(char *file_path, char **lines);
static int Get_Bitmap_Config(bitmap_config_ptr config, char far *line);
static int Create_Bitmap_Asset(pcx_image_ptr image, bitmap_asset_ptr asset, bitmap_config_ptr config);
static int Add_Asset_To_Store(asset_ptr asset);
static void Free_Bitmap_Asset(bitmap_asset_ptr asset);

#endif