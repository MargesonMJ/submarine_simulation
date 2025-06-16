/**
 * @file geometry.h
 * @brief 3D geometry utility types and function
 *        declarations for vector math operations.
 *
 * This header defines basic 3D point and vector types and
 * declares utility functions for vector normalization, cross
 * product calculation, angle conversions, and direction/normal
 * vector calculations for 3D graphics applications.
 */


#pragma once


#include <GL/freeglut.h>


#define PI 3.14159265f  // value of PI


typedef GLfloat point_3d[3];   // { x, y, z }
typedef GLfloat vector_3d[3];  // { x, y, z }


/**
 * @brief Normalize a 3D vector to unit length.
 *
 * Modifies the input vector in-place.
 *
 * @param vector The vector to normalize.
 */
void geometry_normalize_vector(vector_3d vector);

/**
 * @brief Check if a 3D vector is a zero vector (all components are zero).
 *
 * @param vector The vector to check.
 * @return int Returns 1 if the vector is zero, 0 otherwise.
 */
int geometry_is_zero_vector(vector_3d vector);

/**
 * @brief Compute the cross product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @param result The resulting vector from the cross product.
 */
void geometry_cross_product(
    const vector_3d a, 
    const vector_3d b, 
          vector_3d result
);

/**
 * @brief Convert an angle from degrees to radians.
 *
 * @param degree Angle in degrees.
 * @return GLfloat Angle in radians.
 */
GLfloat geometry_degree_to_radian(const GLfloat degree);

/**
 * @brief Convert an angle from radians to degrees.
 *
 * @param radian Angle in radians.
 * @return GLfloat Angle in degrees.
 */
GLfloat geometry_radian_to_degree(const GLfloat radian);

/**
 * @brief Calculate the pitch angle (in degrees) from a 3D vector.
 *
 * Pitch is the angle of elevation relative to the horizontal plane.
 *
 * @param vector The input vector.
 * @return GLfloat Pitch angle in degrees.
 */
GLfloat geometry_calculate_pitch_degree(const vector_3d vector);

/**
 * @brief Calculate the yaw angle (in degrees) from a 3D vector.
 *
 * Yaw is the horizontal rotation angle around the vertical axis.
 *
 * @param vector The input vector.
 * @return GLfloat Yaw angle in degrees.
 */
GLfloat geometry_calculate_yaw_degree(const vector_3d vector);

/**
 * @brief Calculate a normalized direction vector from pitch and yaw angles.
 *
 * @param pitch Pitch angle in radians.
 * @param yaw Yaw angle in radians.
 * @param direction The resulting normalized direction vector.
 */
void geometry_calculate_direction(
    const GLfloat   pitch, 
    const GLfloat   yaw, 
          vector_3d direction
);

/**
 * @brief Calculate the surface normal vector from three 3D points.
 *
 * The resulting normal vector is normalized.
 *
 * @param p1 First point of the triangle.
 * @param p2 Second point of the triangle.
 * @param p3 Third point of the triangle.
 * @param normal The resulting normalized normal vector.
 */
void geometry_calculate_normal(
    const point_3d  p1, 
    const point_3d  p2, 
    const point_3d  p3, 
          vector_3d normal
);
