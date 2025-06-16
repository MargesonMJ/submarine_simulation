/**
 * @file scene_object.h
 * @brief Defines a 3D object in the scene, including
 *        transformation and material properties.
 */


#pragma once


#include "mesh.h"
#include "lighting.h"

#include <GL/freeglut.h>


/**
 * @brief Represents a 3D object loaded from an OBJ file.
 */
typedef struct {
    point_3d  position;   // position of the object in 3D space
    vector_3d direction;  // direction the object is facing
    GLfloat   speed;      // movement speed of the object
    GLfloat   rotation;   // rotation offset (used for correcting model orientation)
    GLfloat   scale;      // scale factor
    mesh      mesh;       // mesh data of the object
    color     ambient;    // ambient color of the object
    color     diffuse;    // diffuse color of the object
    color     specular;   // specular color of the object
    GLfloat   shine;      // shininess coefficient for specular lighting
} scene_object;


/**
 * @brief Frees any memory allocated by the object's mesh.
 *
 * @param object Pointer to the scene object to clean up.
 */
void scene_object_cleanup(scene_object* object);


/**
 * @brief Initializes a scene object from a local OBJ file.
 *
 * @param object Pointer to the scene object to initialize.
 * @param local_file_path Path to the local .obj file.
 */
void scene_object_initialize(scene_object* object, const char* local_file_path);
