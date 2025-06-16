/**
 * @file scene_object.c
 * @brief Implementation for scene object initialization and cleanup.
 */


#include "scene_object.h"


 /**
  * @brief Frees memory associated with a scene object's mesh.
  *
  * This function should be called when the object is no longer needed.
  * It prevents memory leaks by freeing dynamically allocated mesh data.
  *
  * @param object Pointer to the scene object.
  */
void scene_object_cleanup(scene_object* object)
{
    mesh_cleanup(&object->mesh);
}

/**
 * @brief Initializes a scene object using data from a .obj file.
 *
 * This sets up the mesh, position, direction, colors, and other
 * default values necessary for rendering or simulation.
 *
 * @param object Pointer to the scene object to initialize.
 * @param local_file_path Path to the local .obj file used to load mesh data.
 */
void scene_object_initialize(scene_object* object, const char* local_file_path)
{
    mesh_initialize(&object->mesh, local_file_path);

    for (int i = 0; i < 4; ++i)
    {
        if (i < 3)
        {
            object->position[i] = 0.0f;
            object->direction[i] = 0.0f;
        }

        object->ambient[i] = 0.0f;
        object->diffuse[i] = 1.0f;
        object->specular[i] = 0.0f;
    }

    object->speed = 0.0f;
    object->rotation = 0.0f;
    object->scale = 1.0f;
    object->shine = 0.0f;
}
