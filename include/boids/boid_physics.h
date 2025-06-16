/**
 * @file boid_physics.h
 * @brief Declares physics-related functions for boids
 *        including distance calculations, wall detection,
 *        target rotations for behaviors, and position updates.
 *
 * This header provides:
 * - Distance calculations between boids and to walls
 * - Target rotation calculations for wall avoidance and neighbor interactions
 * - Position updates based on rotation and speed
 */


#pragma once


#include "boids/boids.h"
#include "boids/boid_behavior.h"


/**
 * @brief Calculates and returns the distance between two given boids.
 *
 * @param b1 The first boid.
 * @param b2 The second boid.
 * @return GLfloat The Euclidean distance between the two boids.
 */
GLfloat boid_physics_distance_of_boids(const boid b1, const boid b2);

/**
 * @brief Calculates and returns the minimum distance
 *        from the subject boid to the closest wall.
 *
 * Called each frame for each boid to determine if
 * it should avoid the wall or move with neighbors.
 *
 * @param subject_boid The boid to measure distance to the environment.
 * @return GLfloat The minimum distance to any wall of the environment.
 */
GLfloat boid_physics_min_distance_to_environment(const boid subject_boid);

/**
 * @brief Computes the target direction vector
 *        for the subject boid to avoid walls.
 *
 * The direction is inversely proportional
 * to the distance from environment edges.
 *
 * @param subject_boid The boid to calculate avoidance direction for.
 * @param target_direction Pointer to a 3D vector to store
 *                         the resulting target direction.
 */
void boid_physics_target_direction_environment(
    const boid       subject_boid,
          vector_3d* target_direction
);

/**
 * @brief Computes the target direction for the subject
 *        boid to align its direction with neighbors.
 *
 * @param subject_boid The boid whose alignment is computed.
 * @param neighbors Array of neighbor boids influencing alignment.
 * @param target_direction Pointer to a 3D vector to store
 *                         the resulting alignment direction.
 */
void boid_physics_target_direction_neighbor_alignment(
    const boid           subject_boid,
    const boid_neighbor* neighbors,
          vector_3d*     target_direction
);

/**
 * @brief Computes the target direction for the
 *        subject boid to cohere toward neighbors.
 *
 * The cohesion vector is weighted inversely
 * by the squared distance to each neighbor.
 *
 * @param subject_boid The boid whose cohesion is computed.
 * @param neighbors Array of neighbor boids influencing cohesion.
 * @param target_direction Pointer to a 3D vector to store
 *                         the resulting cohesion direction.
 */
void boid_physics_target_direction_neighbor_cohesion(
    const boid subject_boid,
    const boid_neighbor* neighbors,
    vector_3d* target_direction
);

/**
 * @brief Updates the position of the subject
 *        boid based on its direction and speed.
 *
 * Called once per frame for each boid.
 *
 * @param subject_boid Pointer to the boid to update.
 */
void boid_physics_update_position(boid* subject_boid);
