/**
 * @file camera.h
 * @brief Defines the main camera structure and update function.
 *
 * Provides default camera parameters and a camera_update function
 * to position the camera relative to the submarine object.
 */


#pragma once


#include "geometry.h"


#define DEFAULT_CAMERA_POSITION { -1.0f, 2.0f, -2.0f }  // default starting position
#define DEFAULT_CAMERA_FORWARD  {  0.0f, 0.0f,  1.0f }  // default camera forward direction
#define DEFAULT_CAMERA_LOOK_AT  {  0.0f, 0.0f,  0.0f }  // default position for camera to face

#define DEFAULT_CAMERA_THETA    ( PI )           // default camera theta angle
#define DEFAULT_CAMERA_PHI      ( PI / 180.0f )  // default camera phi angle

#define DEFAULT_CAMERA_FOV        110.0  // default camera field-of-view.
#define DEFAULT_CAMERA_NEAR_PLANE   0.1  // default camera clipping near plane
#define DEFAULT_CAMERA_FAR_PLANE  100.0  // default camera clipping far plane


/**
 * @brief Represents the camera state in 3D space.
 *
 * Contains position, forward direction, look-at point,
 * spherical angles theta and phi, and field of view.
 */
typedef struct {
    point_3d  position;  // camera position in world coordinates
    vector_3d forward;   // forward direction vector
    point_3d  look_at;   // point camera is looking at
    GLfloat   theta;     // azimuthal angle in radians
    GLfloat   phi;       // polar angle in radians
    GLdouble  fov;       // field of view in degrees
} camera;


// Global main camera settings and properties.
extern camera main_camera;


/**
 * @brief Updates the main_camera position based on the submarine position.
 *
 * Positions the camera at a fixed distance from the submarine,
 * computed using spherical coordinates (theta, phi).
 * Updates the camera's look_at point to the submarine's position.
 */
void camera_update(void);
