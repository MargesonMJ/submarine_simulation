/**
 * @file texture.h
 * @brief Texture loading interface for OpenGL.
 *
 * Provides functionality to load an image file
 * and generate an OpenGL texture from it.
 */


#pragma once

#include <GL/freeglut.h>


/**
 * @brief Loads an image from a file and creates an OpenGL texture.
 *
 * This function loads the image located at `local_file_path` into memory,
 * generates a new OpenGL texture ID, and uploads the image data to the GPU.
 * The texture uses mipmaps and linear filtering.
 *
 * @param local_file_path The path to the image file to load.
 * @return GLuint The generated OpenGL texture ID.
 */
GLuint texture_create_from_file(const char* local_file_path);
