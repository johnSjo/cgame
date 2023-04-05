#ifndef POLYGON_H
#define POLYGON_H

#include <stdlib.h>
#include <math.h>
#include "vmode.h"
#include "vec.h"

// PROTOTYPES
void Render_Line(vec2 point, vec2 end, char color);
vec2 Rotate_Point(vec2 point, vec2 anchor, double angle);

#endif