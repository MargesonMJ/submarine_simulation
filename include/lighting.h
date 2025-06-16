/**
 * @file lighting.h
 * @brief Interface for setting up scene lighting.
 */


#pragma once


#include <GL/freeglut.h>


typedef GLfloat color[4];  // { r, g, b, a }


/**
 * @brief Initializes global and directional lighting for the scene.
 */
void lighting_initialize(void);
