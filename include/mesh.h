/**
 * @file mesh.h
 * @brief Defines data structures and functions for handling 3D mesh models.
 */


#pragma once


#include "geometry.h"


/**
 * @brief A single triangular face in a mesh, storing vertex and normal indices.
 */
typedef struct {
    int vertex_numbers[3]; /**< Indices of the vertices */
    int normal_numbers[3]; /**< Indices of the normals */
} mesh_face;

/**
 * @brief A structure holding vertices, normals, and faces of a 3D model.
 */
typedef struct {
    point_3d* vertices;      // array of vertex coordinates
    vector_3d* normals;      // array of normal vectors
    mesh_face* faces;        // array of mesh faces
    int        vertex_count; // number of vertices
    int        normal_count; // number of normals
    int        face_count;   // number of faces
} mesh;


/**
 * @brief Frees memory allocated for the mesh.
 *
 * @param mesh Pointer to the mesh to clean up.
 */
void mesh_cleanup(mesh* mesh);

/**
 * @brief Loads mesh data from a local .obj file.
 *
 * @param mesh Pointer to the mesh structure to populate.
 * @param local_file_path Path to the .obj file.
 */
void mesh_initialize(mesh* mesh, const char* local_file_path);
