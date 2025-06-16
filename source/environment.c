/**
 * @file environment.c
 * @brief Implementation of environment initialization functions.
 *
 * Creates quadric objects and loads environment textures.
 */


#include "environment.h"

#include "texture.h"

#include <GL/glu.h>


GLUquadric* quadric_environment;    // quadric object used for floor and walls
GLuint      texture_id_environment; // texture ID for environment surface
GLUquadric* quadric_origin_sphere;  // quadric object for rendering origin sphere


/**
 * @brief Initialize environment quadrics and textures.
 *
 * Creates new quadrics for the environment and origin sphere,
 * enables texture mapping on the environment quadric,
 * and loads the sand texture for the environment floor and walls.
 */
void environment_initialize(void)
{
    quadric_environment = gluNewQuadric();
    gluQuadricTexture(quadric_environment, GL_TRUE);

    texture_id_environment = 
        texture_create_from_file("resources/assets/textures/sand.jpg");

    quadric_origin_sphere = gluNewQuadric();
}
