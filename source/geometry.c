/**
 * @file geometry.c
 * @brief Implementation of 3D geometry utility functions.
 *
 * Contains vector normalization, cross product, angle conversions,
 * and calculations for direction and normal vectors.
 */

#include "geometry.h"
#include <math.h>

#define DEGREE_TO_RADIAN (PI / 180.0f)

/**
 * @brief Normalize a 3D vector to unit length.
 *
 * Modifies the input vector in-place.
 *
 * @param vector The vector to normalize.
 */
void geometry_normalize_vector(vector_3d vector)
{
    const GLfloat length = 
        sqrt(
            vector[0] * vector[0] +
            vector[1] * vector[1] +
            vector[2] * vector[2]
        );

    vector[0] = vector[0] / length;
    vector[1] = vector[1] / length;
    vector[2] = vector[2] / length;
}

/**
 * @brief Check if a 3D vector is a zero vector (all components zero).
 *
 * @param vector The vector to check.
 * @return int Returns 1 if the vector is zero, 0 otherwise.
 */
int geometry_is_zero_vector(vector_3d vector)
{
    for (int i = 0; i < 3; ++i)
    {
        if (vector[i] != 0.0) return 0;
    }

    return 1;
}

/**
 * @brief Calculate the cross product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param result The resulting cross product vector.
 */
void geometry_cross_product(
    const vector_3d a, 
    const vector_3d b, 
          vector_3d result
)
{
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

/**
 * @brief Convert degrees to radians.
 *
 * @param degree Angle in degrees.
 * @return GLfloat Angle in radians.
 */
GLfloat geometry_degree_to_radian(const GLfloat degree)
{
    return degree * DEGREE_TO_RADIAN;
}

/**
 * @brief Convert radians to degrees.
 *
 * @param radian Angle in radians.
 * @return GLfloat Angle in degrees.
 */
GLfloat geometry_radian_to_degree(const GLfloat radian)
{
    return radian / DEGREE_TO_RADIAN;
}

/**
 * @brief Calculate pitch angle (degrees) from a vector.
 *
 * Pitch is the vertical angle, elevation from the horizontal.
 *
 * @param vector Input 3D vector.
 * @return GLfloat Pitch angle in degrees.
 */
GLfloat geometry_calculate_pitch_degree(const vector_3d vector)
{
    return geometry_radian_to_degree(asinf(vector[1]));
}

/**
 * @brief Calculate yaw angle (degrees) from a vector.
 *
 * Yaw is the horizontal rotation angle around the vertical axis.
 *
 * @param vector Input 3D vector.
 * @return GLfloat Yaw angle in degrees.
 */
GLfloat geometry_calculate_yaw_degree(const vector_3d vector)
{
    return geometry_radian_to_degree(atan2f(vector[0], vector[2]));
}

/**
 * @brief Calculate a normalized direction vector from pitch and yaw angles.
 *
 * @param pitch Pitch angle in radians.
 * @param yaw Yaw angle in radians.
 * @param direction Output normalized direction vector.
 */
void geometry_calculate_direction(
    const GLfloat   pitch, 
    const GLfloat   yaw, 
          vector_3d direction
)
{
    direction[0] = cosf(pitch) * cosf(yaw);
    direction[1] = sinf(yaw);
    direction[2] = cosf(pitch) * sinf(yaw);

    geometry_normalize_vector(direction);
}

/**
 * @brief Calculate the normal vector of a triangle defined by three points.
 *
 * The normal is normalized and points per the right-hand rule.
 *
 * @param p1 First vertex of the triangle.
 * @param p2 Second vertex of the triangle.
 * @param p3 Third vertex of the triangle.
 * @param normal Output normalized normal vector.
 */
void geometry_calculate_normal(
    const point_3d  p1, 
    const point_3d  p2, 
    const point_3d  p3, 
          vector_3d normal
)
{
    vector_3d e1 = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    vector_3d e2 = { p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };

    normal[0] = e1[1] * e2[2] - e1[2] * e2[1];
    normal[1] = e1[2] * e2[0] - e1[0] * e2[2];
    normal[2] = e1[0] * e2[1] - e1[1] * e2[0];

    geometry_normalize_vector(normal);
}
