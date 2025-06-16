/**
 * @file environment.h
 * @brief Environment module for rendering floor, walls, and origin sphere.
 *
 * Defines constants and declarations for environment geometry and textures.
 */


#pragma once


#include <GL/freeglut.h>


#define ENVIRONMENT_RADIUS_XZ   10  // radius of environment floor and walls in XZ plane
#define ENVIRONMENT_HEIGHT      10  // height of the environment 
#define ENVIRONMENT_FLOOR_Y   (-1)  // y coordinate of the floor


extern GLUquadric* quadric_environment;    // quadric object used for floor and walls
extern GLuint      texture_id_environment; // texture ID for environment surface
extern GLUquadric* quadric_origin_sphere;  // quadric object for rendering origin sphere


/**
 * @brief Initialize environment resources like quadrics and textures.
 */
void environment_initialize(void);
