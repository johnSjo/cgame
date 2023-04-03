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
#include "frame.h"

// ENUMS

typedef enum Asset_Variant
{
  SPRITE_SHEET,
  IMAGE,
  PALETTE
} Asset_Variant;

// STRUCTS

typedef struct sprite_sheet_frame_type
{
  uchar far *buffer; // The pointer to the image data
  char transparent;  // 0 = opaque, 1 = has some transparent pixels
  vec2 dimension;    // The size of the sprite_sheet_frame
} sprite_sheet_frame, *sprite_sheet_frame_ptr;

typedef struct sprite_sheet_config_type
{
  char id[32];
  char path[128];
  vec2 dimension;
} sprite_sheet_config, *sprite_sheet_config_ptr;

typedef struct sprite_sheet_asset_type
{
  char far *id;
  Asset_Variant variant;
  uchar number_of_frames;
  sprite_sheet_frame_ptr far **frames;
} sprite_sheet_asset, *sprite_sheet_asset_ptr;

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
static int Add_Asset_To_Store(asset_ptr asset);
static int Get_Sprite_Sheet_Config(sprite_sheet_config_ptr config, char far *line);
static int Create_Sprite_Sheet_Asset(pcx_image_ptr image, sprite_sheet_asset_ptr asset, sprite_sheet_config_ptr config);
static int Init_Sprite_Sheet_Asset(sprite_sheet_asset_ptr asset, sprite_sheet_config_ptr config, uchar number_of_frames);
static void Free_Sprite_Sheet_Asset(sprite_sheet_asset_ptr asset);

#endif