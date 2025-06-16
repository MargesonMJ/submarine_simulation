/**
 * @file boid_behavior.h
 * @brief Declarations for boid flocking behaviors:
 *        neighbor detection, wall avoidance, and movement rules.
 *
 * Defines constants, types, and function prototypes
 * to implement flocking behavior for boids, including:
 * - Detecting nearby neighbors within a set radius
 * - Detecting proximity to environment boundaries (walls)
 * - Steering boids to align with neighbors, separate to avoid collisions,
 *   and cohere towards the group's center
 * - Repelling boids from walls to keep them inside the environment
 *
 * These behaviors enable realistic flocking simulations based on classic
 * rules of alignment, separation, and cohesion.
 */


#pragma once


#include "boids.h"


// Distance thresholds.
#define BOID_TRIGGER_SEPARATE    1.0f  // distance at which boids repel one another.
#define BOID_TRIGGER_ENVIRONMENT 2.0f  // distance at which boids repel from the environment.

// Strength factors for different behavior forces.
#define BOID_STRENGTH_ENVIRONMENT 0.1f
#define BOID_STRENGTH_SEPARATE    0.005f
#define BOID_STRENGTH_ALIGNMENT   0.00125f
#define BOID_STRENGTH_COHESION    0.002f


/**
 * @brief Represents a neighboring boid with
 *        distance and index in the boid array.
 */
typedef struct {
    GLfloat distance;  // distance from the subject boid
    size_t  index;     // index of the neighbor boid in the global array
} boid_neighbor;


/**
 * @brief Finds the closest neighboring boids to a given boid.
 *
 * Searches through all boids and returns the closest
 * neighbors sorted by distance, excluding the subject itself.
 *
 * @param subject_boid The boid whose neighbors are to be found.
 * @param neighbors Array to store the found neighbors.
 */
void boid_behavior_find_neighbors(boid subject_boid, boid_neighbor* neighbors);

/**
 * @brief Determines if the boid is near enough to
 *        a wall to trigger avoidance behavior.
 *
 * @param subject_boid The boid to test for wall proximity.
 * @return int Returns 1 if wall avoidance should be triggered, 0 otherwise.
 */
int boid_behavior_environment_trigger(boid subject_boid);

/**
 * @brief Applies a repulsion force to steer the boid away from nearby walls.
 *
 * @param subject_boid Pointer to the boid to be adjusted.
 */
void boid_behavior_handle_environment(boid* subject_boid);

/**
 * @brief Applies flocking behaviors of alignment,
 *        separation, and cohesion relative to neighbors.
 *
 * Called when the boid is not near a wall. Boids align
 * direction with neighbors, maintain separation if too
 * close, and move toward the average position of neighbors.
 *
 * @param subject_boid Pointer to the boid to update.
 */
void boid_behavior_handle_neighbors(boid* subject_boid);
