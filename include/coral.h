/**
 * @file coral.h
 * @brief Defines the coral objects and their management functions.
 *
 * Manages an array of coral scene objects, including
 * initialization and cleanup.
 */


#pragma once


#include "scene_object.h"


#define CORAL_COUNT  14       // number of coral objects
#define CORAL_HEIGHT (-1.0f)  // y position of each coral object.


// Global array of coral scene objects.
extern scene_object objects_coral[CORAL_COUNT];


/**
 * @brief Initializes all coral objects, loading
 *        their meshes and setting positions.
 */
void coral_initialize(void);

/**
 * @brief Cleans up all coral objects, freeing any allocated resources.
 */
void coral_cleanup(void);
