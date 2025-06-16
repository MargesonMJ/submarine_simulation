/**
 * @file submarine.c
 * @brief Implements the submarine scene object.
 *
 * Loads the submarine mesh, sets default properties, updates movement,
 * and cleans up resources.
 */


#include "submarine.h"


// Global submarine scene object.
scene_object object_submarine;


/**
 * @brief Initializes the submarine object.
 *
 * Loads the mesh from file and sets default position, color,
 * rotation, scale, and shininess values.
 */
void submarine_initialize(void)
{
    point_3d submarine_position = { 0.0f, 2.0f, -2.0f };
    color    diffuse_yellow = { 1.0f, 1.0f,  0.0f, 0.0f };
    color    specular_white = { 1.0f, 1.0f,  1.0f, 0.0f };

    scene_object_initialize(
        &object_submarine, 
        "resources/assets/submarine/submarine-smooth.txt"
    );

    for (int i = 0; i < 3; ++i)
    {
        object_submarine.position[i] = submarine_position[i];
        object_submarine.diffuse[i] = diffuse_yellow[i];
        object_submarine.specular[i] = specular_white[i];
    }

    object_submarine.rotation = DEFAULT_SUBMARINE_ROTATION;
    object_submarine.scale = DEFAULT_SUBMARINE_SCALE;
    object_submarine.shine = DEFAULT_SUBMARINE_SHINE;
}

/**
 * @brief Updates the submarine position based on its direction and speed.
 */
void submarine_update(void)
{
    for (int i = 0; i < 3; ++i)
    {
        object_submarine.position[i] += 
            object_submarine.direction[i] * 
            object_submarine.speed;
    }
}

/**
 * @brief Cleans up resources associated with the submarine.
 */
void submarine_cleanup(void)
{
    scene_object_cleanup(&object_submarine);
}
