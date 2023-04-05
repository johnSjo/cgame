#ifndef CGAME_H
#define CGAME_H

// Standard includes
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

// All includes from the gfxlib

#include "vmode.h"
#include "text.h"
#include "color.h"
#include "pcx.h"
#include "sprite.h"
#include "vec.h"
#include "polygon.h"
#include "entity.h"

// This one currently only deals with gfx assets
// but one day there will be more and then it should be moved out from gfx
#include "assets.h"

// These should probably not live in the gfxlib
#include "typedef.h"
#include "file.h"     // general file handling
#include "math_utl.h" // extra math utillities

#endif