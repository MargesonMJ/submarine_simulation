/**
 * @file texture.c
 * @brief Implements texture loading functionality using stb_image.
 *
 * Uses stb_image to load image files and OpenGL functions
 * to create and configure textures with mipmapping.
 */


#include "texture.h"

#include <stb/stb_image.h>


/**
 * @brief Loads an image from a file and creates an OpenGL texture.
 *
 * Loads the image data using stb_image, generates a texture ID,
 * binds the texture, builds mipmaps, sets min/mag filters, frees image data,
 * and returns the texture ID.
 *
 * @param local_file_path Path to the image file.
 * @return GLuint OpenGL texture ID.
 */
GLuint texture_create_from_file(const char* local_file_path)
{
    GLint width;
    GLint height;
    GLint color_channel_count;

    // Load image data from file using stb_image
    GLubyte* image_data = 
        stbi_load(
            local_file_path, 
            &width, 
            &height, 
            &color_channel_count, 
            0
        );

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Upload texture data and generate mipmaps
    gluBuild2DMipmaps(
        GL_TEXTURE_2D,
        GL_RGB,
        width,
        height,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image_data
    );

    // Set texture filtering parameters for minification and magnification
    glTexParameteri(
        GL_TEXTURE_2D, 
        GL_TEXTURE_MIN_FILTER, 
        GL_LINEAR_MIPMAP_LINEAR
    );
    glTexParameteri(
        GL_TEXTURE_2D, 
        GL_TEXTURE_MAG_FILTER, 
        GL_LINEAR_MIPMAP_LINEAR
    );

    // Free loaded image data from CPU memory
    stbi_image_free(image_data);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}
