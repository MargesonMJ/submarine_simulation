/**
 * @file submarine.h
 * @brief Defines and manages a submarine scene object.
 *
 * Provides constants and functions to initialize, update, and clean up
 * a submarine model represented as a scene_object.
 */

#pragma once

#include "scene_object.h"

#define SUBMARINE_SPEED              0.025f  // default movement speed
#define DEFAULT_SUBMARINE_ROTATION  90.000f  // rotation to properly align the submarine to the scene.
#define DEFAULT_SUBMARINE_SCALE      0.004f  // default submarine object scale
#define DEFAULT_SUBMARINE_YAW       90.000f  // default submarine yaw
#define DEFAULT_SUBMARINE_SHINE    150.000f  // default submarine shine


// Global submarine scene object.
extern scene_object object_submarine;


/**
 * @brief Initializes the submarine object, loading
 *        its mesh and setting default properties.
 */
void submarine_initialize(void);

/**
 * @brief Updates the submarine's position based
 *        on its current direction and speed.
 */
void submarine_update(void);

/**
 * @brief Cleans up resources used by the submarine object.
 */
void submarine_cleanup(void);
