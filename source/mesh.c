/**
 * @file mesh.c
 * @brief Implementation of functions for loading and cleaning mesh data from OBJ files.
 */


#include "mesh.h"
#include <stdio.h>


/**
 * @brief Frees memory allocated for vertices, normals, and faces in a mesh.
 *
 * This function should be called when the mesh
 * is no longer needed to avoid memory leaks.
 *
 * @param mesh Pointer to the mesh structure to clean up.
 */
void mesh_cleanup(mesh* mesh)
{
    free(mesh->vertices);
    free(mesh->normals);
    free(mesh->faces);
}

/**
 * @brief Loads a mesh from an OBJ file.
 *
 * Parses the specified .obj file to extract vertices, normals, and faces.
 * Assumes a specific format with lines starting with 'v', 'vn', and 'f'
 * for vertices, normals, and faces, respectively.
 *
 * @param mesh Pointer to the mesh structure to populate.
 * @param local_file_path Path to the OBJ file to read.
 */
void mesh_initialize(mesh* mesh, const char* local_file_path)
{
    FILE* read_file;
    (void)fopen_s(&read_file, local_file_path, "r");

    char input[256];
    while (fgets(input, sizeof(input), read_file))
    {
        if (input[0] == 'v' && input[1] != 'n')  // Vertex
        {
            mesh->vertices = realloc(
                mesh->vertices,
                sizeof(point_3d) * (mesh->vertex_count + 1)
            );

            sscanf_s(
                input,
                "v %f %f %f",
                &mesh->vertices[mesh->vertex_count][0],
                &mesh->vertices[mesh->vertex_count][1],
                &mesh->vertices[mesh->vertex_count][2]
            );

            mesh->vertex_count++;
        }
        else if (input[1] == 'n')                // Normal
        {
            mesh->normals = realloc(
                mesh->normals,
                sizeof(vector_3d) * (mesh->normal_count + 1)
            );

            sscanf_s(
                input,
                "vn %f %f %f",
                &mesh->normals[mesh->normal_count][0],
                &mesh->normals[mesh->normal_count][1],
                &mesh->normals[mesh->normal_count][2]
            );

            mesh->normal_count++;
        }
        else if (input[0] == 'f')                // Face
        {
            mesh->faces = realloc(
                mesh->faces,
                sizeof(mesh_face) * (mesh->face_count + 1)
            );

            sscanf_s(
                input,
                "f %d//%d %d//%d %d//%d",
                &mesh->faces[mesh->face_count].vertex_numbers[0],
                &mesh->faces[mesh->face_count].normal_numbers[0],
                &mesh->faces[mesh->face_count].vertex_numbers[1],
                &mesh->faces[mesh->face_count].normal_numbers[1],
                &mesh->faces[mesh->face_count].vertex_numbers[2],
                &mesh->faces[mesh->face_count].normal_numbers[2]
            );

            mesh->face_count++;
        }
    }

    (void)fclose(read_file);
}
