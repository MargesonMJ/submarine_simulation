/**
 * @file water.h
 * @brief Provides functionality to initialize and
 *        update a dynamic water surface grid.
 *
 * This module manages a 3D grid of vertices
 * representing a water surface. The grid can be
 * initialized to a flat plane, updated to simulate
 * waves via sine functions, and drawn using OpenGL.
 */


#pragma once


#include "geometry.h"


#define WATER_GRID_SIZE 100  // number of water grid squares


// Global water vertices for drawing.
extern point_3d water_vertices[WATER_GRID_SIZE + 1][WATER_GRID_SIZE + 1];


/**
 * @brief Initializes the water grid vertices to
 *        a flat plane centered at the origin.
 *
 * Sets the X and Z coordinates spaced evenly over a square region,
 * and sets all Y coordinates (height) to 0.
 */
void water_initialize(void);

/**
 * @brief Updates the water surface vertex heights to simulate waves.
 *
 * Adjusts the Y coordinate of each vertex based on a sine wave
 * that varies over time and position to create an animated water effect.
 */
void water_update(void);
