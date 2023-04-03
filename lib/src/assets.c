#include "assets.h"

#define MAX_NUMBER_OF_ASSETS 32
#define MAX_NUMBER_CONFIG_LINES 256

// GLOBALS
static asset_ptr assets_store[MAX_NUMBER_OF_ASSETS];

// FUNCTIONS
int Init_Assets_Store()
{
  int i;
  char far *lines[MAX_NUMBER_CONFIG_LINES];
  char far *line;
  bitmap_config config;
  bitmap_asset_ptr asset;
  pcx_image image;

  // Clear the assets store
  for (i = 0; i < MAX_NUMBER_OF_ASSETS; i++)
    assets_store[i] = NULL;

  // Bitmaps
  _fmemset(lines, NULL, sizeof(lines));

  if (Read_Config_File("assets/configs/bitmaps.cfg", lines))
    return 1;

  i = 0;
  while (lines[i])
  {
    if (Get_Bitmap_Config(&config, lines[i]))
      return 1;

    if (PCX_Load(config.path, &image))
      return 1;

    // TEMP: use a palette asset instead
    if (i == 0)
      PCX_Enable_Palette(&image);

    asset = _fmalloc(sizeof(bitmap_asset));

    if (Create_Bitmap_Asset(&image, asset, &config))
      return 1;

    if (Add_Asset_To_Store((asset_ptr)asset))
      return 1;

    PCX_Delete(&image);

    i++;
  }

  // Free temp config stuff
  for (i = 0; i < MAX_NUMBER_CONFIG_LINES; i++)
    _ffree(lines[i]);

  return 0;
}

static int Add_Asset_To_Store(asset_ptr asset)
{
  int i = 0;

  // find the next empty slot
  while (assets_store[i] && i < MAX_NUMBER_OF_ASSETS)
    i++;

  if (i >= MAX_NUMBER_OF_ASSETS)
  {
    printf("\nError, assets_store is full.");
    return 1;
  }

  assets_store[i] = asset;
  return 0;
}

static int Create_Bitmap_Asset(pcx_image_ptr image, bitmap_asset_ptr asset, bitmap_config_ptr config)
{
  int x, y;
  uchar frame_width = config->dimension.x;
  uchar frame_height = config->dimension.y;
  uchar horizontal_frames = (image->header.width + 1) / frame_width;
  uchar vertical_frames = (image->header.height + 1) / frame_height;
  uchar number_of_frames = horizontal_frames * vertical_frames;
  uchar far *buffer = NULL;
  vec2 offset;
  frame_ptr bitmap_frame;

  asset->id = _fmalloc(sizeof(config->id));
  asset->variant = BITMAP;
  asset->number_of_frames = number_of_frames;
  asset->frames = (frame_ptr far **)_fmalloc(sizeof(frame_ptr far *) * number_of_frames);

  _fstrcpy(asset->id, config->id);

  for (y = 0; y < vertical_frames; y++)
  {
    for (x = 0; x < horizontal_frames; x++)
    {
      offset.x = x * frame_width;
      offset.y = y * frame_height;
      if (PCX_Create_Section(&buffer, image, offset, config->dimension))
        return 1;

      bitmap_frame = _fmalloc(sizeof(frame));
      bitmap_frame->buffer = buffer;
      bitmap_frame->transparent = 0; // TODO: For now
      bitmap_frame->dimension.x = frame_width;
      bitmap_frame->dimension.y = frame_height;

      asset->frames[y * horizontal_frames + x] = (frame_ptr far *)bitmap_frame;
    }
  }

  return 0;
}

static int Get_Bitmap_Config(bitmap_config_ptr config, char far *line)
{
  int width;
  int height;

  if (sscanf(line, "%[^,],%[^,],%d,%d", config->id, config->path, &width, &height) != 4)
  {
    printf("\nError reading config line.");
    return 1;
  }

  config->dimension.x = width;
  config->dimension.y = height;

  return 0;
};

asset_ptr Get_Asset(char *id)
{
  int i = 0;
  asset_ptr asset_ptr;

  while (i < MAX_NUMBER_OF_ASSETS)
  {
    asset_ptr = assets_store[i];
    if (_fstrcmp(asset_ptr->id, id) == 0)
      return assets_store[i];

    i++;
  }

  return NULL;
}

static int Read_Config_File(char *file_path, char **lines)
{
  int i;
  char line[256];
  char far *string;
  int line_count = 0;
  FILE *file_ptr = fopen(file_path, "r");

  if (file_ptr == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }

  while (fgets(line, sizeof(line), file_ptr))
    line_count++;

  fseek(file_ptr, 0, SEEK_SET);

  for (i = 0; i < line_count; i++)
  {
    string = _fmalloc(sizeof(line));
    fgets(string, sizeof(line), file_ptr);
    lines[i] = string;
  }

  fclose(file_ptr);

  return 0;
}

void Free_Assets_Store(void)
{
  int i;
  asset_ptr asset;

  // Clear the assets store
  for (i = 0; i < MAX_NUMBER_OF_ASSETS; i++)
  {
    asset = assets_store[i];

    switch (asset->variant)
    {
    case BITMAP:
      Free_Bitmap_Asset((bitmap_asset_ptr)asset);
      break;

      // TODO: add functions for the other asset variants
    default:
      break;
    }
  }
}

static void Free_Bitmap_Asset(bitmap_asset_ptr asset)
{
  int i;

  for (i = 0; i < asset->number_of_frames; i++)
    Free_Frame((frame_ptr)asset->frames[i]);

  _ffree(asset->id);
  _ffree(asset->frames);
  _ffree(asset);
}