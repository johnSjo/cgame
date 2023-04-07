#include "polygon.h"

void render_line(vec2 start, vec2 end, char color)
{
  int dx = abs(end.x - start.x), sx = start.x < end.x ? 1 : -1;
  int dy = abs(end.y - start.y), sy = start.y < end.y ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  while (1)
  {
    Plot_Pixel_Fast(start.x, start.y, color);
    if (start.x == end.x && start.y == end.y)
      break;

    e2 = err;
    if (e2 > -dx)
    {
      err -= dy;
      start.x += sx;
    }

    if (e2 < dy)
    {
      err += dx;
      start.y += sy;
    }
  }
}

vec2 rotate_point(vec2 point, vec2 anchor, double angle)
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

mesh_ptr init_mesh(char *id, vertex_ptr *vertices, int number_of_vertices, int *indices, int number_of_indices, char color)
{
  mesh_ptr mesh;

  if (!(mesh = _fmalloc(sizeof(struct mesh_type))))
  {
    printf("\nError, initialize mech id: %s, failed to allocate memory.", id);
    return NULL;
  };

  mesh->type = MESH;
  _fstrcpy(mesh->id, id);
  mesh->transform.position.x = 0.0;
  mesh->transform.position.y = 0.0;
  mesh->transform.scale.x = 1.0;
  mesh->transform.scale.y = 1.0;
  mesh->transform.rotation = 0.0;
  mesh->vertices = vertices;
  mesh->number_of_vertices = number_of_vertices;
  mesh->indices = indices;
  mesh->number_of_indices = number_of_indices;
  mesh->color = color;
  mesh->children = NULL;
  mesh->number_of_children = NULL;

  return mesh;
}

void render_mesh(mesh_ptr mesh, transform_ptr parent_transform, char parent_has_transformed)
{
  int i;

  if (parent_has_transformed | mesh->has_transformed)
  {
    // calc new world_transform
    calc_mesh_world_transform(mesh, parent_transform);

    // calc new world_position for each vertex
    for (i = 0; i < mesh->number_of_vertices; i++)
    {
      mesh->vertices[i]->world_position.x = (int)(mesh->vertices[i]->position.x + mesh->transform.position.x + 0.5);
      mesh->vertices[i]->world_position.y = (int)(mesh->vertices[i]->position.y + mesh->transform.position.y + 0.5);
    }
    mesh->has_transformed = 1;
  }

  render_triangle_strip(mesh->vertices, mesh->indices, mesh->number_of_indices, mesh->color);

  for (i = 0; i < mesh->number_of_children; i++)
  {
    render_mesh(mesh->children[i], &(mesh->world_transform), mesh->has_transformed);
  }

  mesh->has_transformed = 0;
}

static void render_triangle_strip(vertex_ptr *vertices, int *indices, int number_of_indices, char color)
{
  int i;
  int left_pixel[SCREEN_HEIGHT];
  int right_pixel[SCREEN_HEIGHT];
  int first_row = 0, last_row = 0;
  vec2 point_one, point_two;

  // maybe do a check that number_of_indices is a factor of three

  for (i = 0; i < number_of_indices; i += 3)
  {
    render_line(vertices[indices[i]]->world_position, vertices[indices[i + 1]]->world_position, color);
    render_line(vertices[indices[i + 1]]->world_position, vertices[indices[i + 2]]->world_position, color);
    render_line(vertices[indices[i + 2]]->world_position, vertices[indices[i]]->world_position, color);
  }
}

static void calc_mesh_world_transform(mesh_ptr mesh, transform_ptr parent_transform)
{
  mesh->world_transform.position.x = mesh->transform.position.x + parent_transform->position.x;
  mesh->world_transform.position.y = mesh->transform.position.y + parent_transform->position.y;

  // scale and rotate for later
}