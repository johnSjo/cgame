#include "cgame.h"

// int main(int argc, char *argv[])
int main(void)
{
    int number_of_vertices = 4;
    int number_of_indices = 6;
    vertex_ptr *vertices = _fmalloc(sizeof(vertex) * number_of_vertices);
    int far *indices = _fmalloc(sizeof(int) * number_of_indices);
    mesh_ptr triangle;
    transform world_position;

    world_position.position.x = 0.0;
    world_position.position.y = 0.0;

    vertices[0]->position.x = -60.0;
    vertices[0]->position.y = -70.0;
    vertices[1]->position.x = 40.0;
    vertices[1]->position.y = -20.0;
    vertices[2]->position.x = -130.0;
    vertices[2]->position.y = 30.0;
    vertices[3]->position.x = -150.0;
    vertices[3]->position.y = 0.0;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 3;
    indices[5] = 2;

    triangle = init_mesh("test triangle", vertices, number_of_vertices, indices, number_of_indices, 45);
    triangle->transform.position.x = 160.0;
    triangle->transform.position.y = 100.0;
    triangle->has_transformed = 1;
    triangle->color = 76;

    Set_Video_Mode(VGA256);

    render_mesh(triangle, &world_position, NULL);
#ifdef PROD
    printf("\nNow we're in production");
#endif

    // Fill_Screen(240);
    while (!kbhit())
    {
        // wait_for_retrace();
    }

    Set_Video_Mode(TEXT_MODE);

    return 0;
}
// // // printf with position
// // // printf("\033[%d;%dHHello, world! %u", 10, 10, i);
