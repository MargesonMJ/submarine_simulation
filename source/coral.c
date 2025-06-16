/**
 * @file coral.c
 * @brief Implements initialization and cleanup for coral objects.
 */


#include "coral.h"

#include <stdio.h>
#include <stdlib.h>


scene_object objects_coral[CORAL_COUNT];  // global array of coral scene objects.
char*        files_coral[CORAL_COUNT];    // file paths to coral object files.


// Predefined fixed positions for each coral object in 3D space.
const point_3d coral_positions[CORAL_COUNT] = {
    {  8.5f, CORAL_HEIGHT,  0.0f },
    {  0.0f, CORAL_HEIGHT,  8.0f },
    {  5.0f, CORAL_HEIGHT,  5.0f },
    {  0.0f, CORAL_HEIGHT,  7.0f },
    { -7.0f, CORAL_HEIGHT,  0.0f },
    { -2.5f, CORAL_HEIGHT, -2.5f },
    {  2.5f, CORAL_HEIGHT, -2.5f },
    { -2.5f, CORAL_HEIGHT,  2.5f },
    { -5.0f, CORAL_HEIGHT,  5.0f },
    {  2.5f, CORAL_HEIGHT,  2.5f },
    {  5.0f, CORAL_HEIGHT, -5.0f },
    { -5.0f, CORAL_HEIGHT, -5.0f },
    {  0.0f, CORAL_HEIGHT, -2.5f },
    {  5.0f, CORAL_HEIGHT,  0.5f }
};


/**
 * @brief Allocates and initializes coral file path strings.
 *
 * Each coral's mesh file path is set to
 * "resources/assets/coral/coral_X.txt"
 * where X is the coral index starting from 1.
 * Also sets the default scale for each coral.
 */
void initialize_coral_files(void)
{
    for (int i = 0; i < CORAL_COUNT; ++i)
    {
        const size_t file_path_max_length = 64;
        files_coral[i] = malloc(file_path_max_length);
        (void)sprintf_s(
            files_coral[i],
            file_path_max_length,
            "resources/assets/coral/coral_%d.txt",
            i + 1
        );
        objects_coral[i].scale = 1.0f;
    }
}

/**
 * @brief Frees the dynamically allocated coral file path strings.
 */
void cleanup_files(void)
{
    for (int i = 0; i < CORAL_COUNT; ++i)
    {
        free(files_coral[i]);
    }
}

/**
 * @brief Initializes all coral objects by loading their meshes
 * and setting their positions and colors.
 */
void coral_initialize(void)
{
    initialize_coral_files();

    const color diffuse_coral = { 0.0f, 1.0f, 0.5f, 1.0f };

    for (int i = 0; i < CORAL_COUNT; ++i)
    {
        scene_object_initialize(&objects_coral[i], files_coral[i]);

        for (int j = 0; j < 3; ++j)
        {
            objects_coral[i].position[j] = coral_positions[i][j];
            objects_coral[i].diffuse[j] = diffuse_coral[j];
        }
        objects_coral[i].scale = 2.0f;
    }

    cleanup_files();
}

/**
 * @brief Cleans up all coral objects, freeing associated resources.
 */
void coral_cleanup(void)
{
    for (int i = 0; i < CORAL_COUNT; ++i)
    {
        scene_object_cleanup(&objects_coral[i]);
    }
}
