#ifndef POLYGON_H
#define POLYGON_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include "vmode.h"
#include "entity.h"
#include "transfor.h"

// STRUCTURES
typedef struct vertex_type
{
  vec2f position;
  vec2 world_position;
  char color;
} vertex, *vertex_ptr;

typedef struct mesh_type
{
  Entity_Type type;            // The type of mesh, should be Entity_Type.MESH
  char id[32];                 // Id/name of the mesh
  transform transform;         // the transformation components
  transform world_transform;   // the transformation components modified by the parent
  char has_transformed;        // flag to indicate the transform has changed, i.e. calculate a new world_transform and pass it to the children
  vertex_ptr *vertices;        // pointer to the vertex data
  int number_of_vertices;      // keep track of how many vertices we have in this mesh
  int *indices;                // the vertices indexes that will be used to build up the mesh, and the order
  int number_of_indices;       // keep track of how many points we have in this mesh, for a triangle mesh it have to be devisable by three
  char color;                  // will override the vertices colors
  struct mesh_type **children; // If the mesh has any children
  int number_of_children;      //
} mesh, *mesh_ptr;

// PROTOTYPES
mesh_ptr init_mesh(char *id, vertex_ptr *vertices, int number_of_vertices, int *indices, int number_of_indices, char color);
void render_line(vec2 start, vec2 end, char color);
vec2 rotate_point(vec2 point, vec2 anchor, double angle);
void render_mesh(mesh_ptr mesh, transform_ptr parent_transform, char parent_has_transformed);

// INTERNALS
static void render_triangle_strip(vertex_ptr *vertices, int *indices, int number_of_indices, char color);
static void calc_mesh_world_transform(mesh_ptr mesh, transform_ptr parent_transform);

#endif