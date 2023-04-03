#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "file.h"
#include "typedef.h"
#include "color.h"
#include "pcx.h"
#include "vec.h"

// ENUMS

typedef enum Asset_Variant
{
  SPRITE_SHEET,
  IMAGE,
  PALETTE
} Asset_Variant;

// STRUCTS

typedef struct sprite_sheet_config_type
{
  char id[32];
  char path[128]; // File path to image
  vec2 dimension; // The size of each frame
} sprite_sheet_config, *sprite_sheet_config_ptr;

typedef struct sprite_sheet_asset_type
{
  char far *id;          // The name/id of the asset
  Asset_Variant variant; // Asset_Variant.SPRITE_SHEET
  char transparent;      // 0 = opaque, 1 = has some transparent pixels, TODO: maybe do this on a per frame level
  vec2 dimension;        // The size of the sprite sheet
  uchar far *buffer;     // The pointer to the image data
  vec2 frame_dimension;  // The size of each frame
  vec2 number_of_frames; // Number horizontal and vertical frames
} sprite_sheet_asset, *sprite_sheet_asset_ptr;

typedef struct image_asset_type
{
  char far *id;
  Asset_Variant variant; // Asset_Variant.IMAGE
  char transparent;      // 0 = opaque, 1 = has some transparent pixels
  vec2 dimension;        // The size of the image
  uchar far *buffer;     // The pointer to the image data
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
static int Add_Asset_To_Store(asset_ptr asset);
static int Get_Sprite_Sheet_Config(sprite_sheet_config_ptr config, char far *line);
static sprite_sheet_asset_ptr Init_Sprite_Sheet_Asset(pcx_image_ptr image, sprite_sheet_config_ptr config);
static void Free_Sprite_Sheet_Asset(sprite_sheet_asset_ptr asset);

#endif