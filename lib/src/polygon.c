#include "polygon.h"

void Render_Line(vec2 point, vec2 end, char color)
{
  int dx = abs(end.x - point.x), sx = point.x < end.x ? 1 : -1;
  int dy = abs(end.y - point.y), sy = point.y < end.y ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  while (1)
  {
    Plot_Pixel_Fast(point.x, point.y, color);
    if (point.x == end.x && point.y == end.y)
      break;

    e2 = err;
    if (e2 > -dx)
    {
      err -= dy;
      point.x += sx;
    }

    if (e2 < dy)
    {
      err += dx;
      point.y += sy;
    }
  }
}

vec2 Rotate_Point(vec2 point, vec2 anchor, double angle)
{
  vec2 new_point;
  // Translate point to origin
  int x_new = point.x - anchor.x;
  int y_new = point.y - anchor.y;

  // Perform rotation
  double cos_angle = cos(angle);
  double sin_angle = sin(angle);
  int x_rotated = x_new * cos_angle - y_new * sin_angle;
  int y_rotated = x_new * sin_angle + y_new * cos_angle;

  // Translate point back to original position
  new_point.x = x_rotated + anchor.x;
  new_point.y = y_rotated + anchor.y;

  return new_point;
}
