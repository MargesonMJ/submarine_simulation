/**
 * @file camera.c
 * @brief Implements camera position updating relative to the submarine.
 */


#include "camera.h"

#include "submarine.h"

#include <corecrt_math.h>


// Global main camera.
camera main_camera = {
    DEFAULT_CAMERA_POSITION,
    DEFAULT_CAMERA_FORWARD,
    DEFAULT_CAMERA_LOOK_AT,
    DEFAULT_CAMERA_THETA,
    DEFAULT_CAMERA_PHI,
    DEFAULT_CAMERA_FOV
};


/**
 * @brief Updates the camera position and look_at to follow the submarine.
 *
 * Calculates camera position as an offset from the submarine's
 * current position, using spherical coordinate angles theta
 * and phi, and a fixed distance. Updates the look_at point to
 * be the submarine's current position.
 */
void camera_update(void)
{
    const GLfloat distance_from_submarine = 1.5f;

    main_camera.position[0] =
        object_submarine.position[0] +
        distance_from_submarine      *
        cosf(main_camera.phi)        *
        sinf(main_camera.theta);

    main_camera.position[1] =
        object_submarine.position[1] +
        distance_from_submarine      *
        sinf(main_camera.phi);

    main_camera.position[2] =
        object_submarine.position[2] +
        distance_from_submarine      *
        cosf(main_camera.phi)        *
        cosf(main_camera.theta);

    for (int i = 0; i < 3; ++i)
    {
        main_camera.look_at[i] = object_submarine.position[i];
    }
}
