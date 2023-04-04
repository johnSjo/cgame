#include "assets.h"

#define MAX_NUMBER_OF_ASSETS 32

// GLOBALS
static asset_ptr assets_store[MAX_NUMBER_OF_ASSETS];

// FUNCTIONS
int Init_Assets_Store()
{
  int i;
  char far *lines[MAX_NUMBER_CONFIG_LINES];
  char far *line;
  sprite_sheet_config config;
  sprite_sheet_asset_ptr asset;
  pcx_image image;

  // Clear the assets store
  for (i = 0; i < MAX_NUMBER_OF_ASSETS; i++)
    assets_store[i] = NULL;

  // Sprite Sheets
  _fmemset(lines, NULL, sizeof(lines));

  if (Read_Config_File("assets/configs/sprsheet.cfg", lines))
    return 1;

  i = 0;
  while (lines[i])
  {
    if (Get_Sprite_Sheet_Config(&config, lines[i]))
      return 1;

    if (PCX_Load(config.path, &image))
      return 1;

    // TEMP: use a palette asset instead
    if (i == 0)
      PCX_Enable_Palette(&image);

    if (!(asset = Init_Sprite_Sheet_Asset(&image, &config)))
      return 1;

    if (Add_Asset_To_Store((asset_ptr)asset))
      return 1;

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

static sprite_sheet_asset_ptr Init_Sprite_Sheet_Asset(pcx_image_ptr image, sprite_sheet_config_ptr config)
{
  sprite_sheet_asset_ptr asset;
  int image_width = (image->header.width + 1);
  int image_height = (image->header.height + 1);

  if (!(asset = _fmalloc(sizeof(sprite_sheet_asset))))
  {
    printf("\nError, initialize sprite sheet asset, failed to allocate asset.");
    return NULL;
  };

  _fstrcpy(asset->id, config->id);

  asset->variant = SPRITE_SHEET;
  asset->transparent = 0;        // For now...
  asset->buffer = image->buffer; // NOTE: this asset takes ownership of the allocated image data
  asset->sheet_dimension.x = image_width;
  asset->sheet_dimension.y = image_height;
  asset->frame_dimension = config->dimension;
  asset->number_of_frames.x = image_width / config->dimension.x;
  asset->number_of_frames.y = image_height / config->dimension.y;

  return asset;
}

static int Get_Sprite_Sheet_Config(sprite_sheet_config_ptr config, char far *line)
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

  while (i < MAX_NUMBER_OF_ASSETS && assets_store[i])
  {
    asset_ptr = assets_store[i];
    if (_fstrcmp(asset_ptr->id, id) == 0)
      return assets_store[i];

    i++;
  }

  return NULL;
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
    case SPRITE_SHEET:
      Free_Sprite_Sheet_Asset((sprite_sheet_asset_ptr)asset);
      break;

      // TODO: add functions for the other asset variants
    default:
      break;
    }
  }
}

static void Free_Sprite_Sheet_Asset(sprite_sheet_asset_ptr asset)
{
  _ffree(asset->buffer);
  _ffree(asset);
}