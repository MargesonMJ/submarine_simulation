/**
 * @file water.c
 * @brief Implements the dynamic water surface grid functionality.
 *
 * Contains functions to initialize the water grid and
 * update vertex heights over time to simulate waves.
 */


#include "water.h"

#include <math.h>
#include <GL/freeglut.h>


// Water grid vertex array.
point_3d water_vertices[WATER_GRID_SIZE + 1][WATER_GRID_SIZE + 1];


/**
 * @brief Initializes the water grid vertices to a flat surface.
 *
 * Sets up the grid vertices evenly spaced over a fixed square region,
 * with initial height (Y) set to 0.
 */
void water_initialize(void)
{
    const GLfloat total_size = 100.0f;
    const float step_x = total_size / WATER_GRID_SIZE;
    const float step_z = total_size / WATER_GRID_SIZE;
    const float start_x = -total_size / 2.0f;
    const float start_z = -total_size / 2.0f;

    for (int i = 0; i <= WATER_GRID_SIZE; ++i)
    {
        for (int j = 0; j <= WATER_GRID_SIZE; ++j)
        {
            const float x = start_x + j * step_x;
            const float z = start_z + i * step_z;
            water_vertices[i][j][0] = x;
            water_vertices[i][j][1] = 0.0f;
            water_vertices[i][j][2] = z;
        }
    }
}

/**
 * @brief Updates the water grid vertex heights to simulate waves.
 *
 * Modifies the Y coordinate of each vertex with a sine wave based on
 * vertex position and elapsed time to create an animated water effect.
 */
void water_update(void)
{
    for (int i = 0; i <= WATER_GRID_SIZE; i++)
    {
        for (int j = 0; j <= WATER_GRID_SIZE; j++)
        {
            water_vertices[i][j][1] = sinf(
                water_vertices[i][j][2] +
                glutGet(GLUT_ELAPSED_TIME) * 0.001f
            ) * 0.5f;
        }
    }
}
