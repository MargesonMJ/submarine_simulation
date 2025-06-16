/**
 * @file boid_behavior.c
 * @brief Implements boid flocking behavior algorithms:
 *        neighbor finding, wall avoidance, and steering.
 *
 * Contains logic for:
 * - Identifying nearest neighbors for each boid
 * - Detecting proximity to environment boundaries and applying repulsion
 * - Steering boids to align with neighbors' directions
 * - Separating boids that are too close to avoid collisions
 * - Moving boids towards the center of their local group for cohesion
 *
 * These combine to simulate natural flocking dynamics.
 */


#include "boids/boid_behavior.h"

#include "boids/boid_physics.h"
#include "environment.h"

#include <stdlib.h>


/**
 * @brief Compare two boid_neighbor structs by their distance.
 *
 * Used internally by qsort to sort neighbors from closest to farthest.
 *
 * @param a Pointer to the first boid_neighbor.
 * @param b Pointer to the second boid_neighbor.
 * @return int Negative if a < b, zero if equal, positive if a > b.
 */
static int compare_neighbor_boids(const void* a, const void* b)
{
    const boid_neighbor* neighbor_a = (const boid_neighbor*)a;
    const boid_neighbor* neighbor_b = (const boid_neighbor*)b;

    if (neighbor_a->distance < neighbor_b->distance) return -1;
    if (neighbor_a->distance > neighbor_b->distance) return 1;
    return 0;
}

/**
 * @brief Sort an array of boid_neighbor structs by distance in ascending order.
 *
 * @param all_neighbors Array of neighbors to sort.
 */
static void sort_all_neighbors(boid_neighbor* all_neighbors)
{
    qsort(
        all_neighbors,
        BOID_COUNT,
        sizeof(boid_neighbor),
        compare_neighbor_boids
    );
}

/**
 * @brief Find the closest neighbors of a given boid.
 *
 * Calculates distances from the subject boid to all other boids,
 * sorts them, and selects the closest neighbors, excluding the subject itself.
 *
 * @param subject_boid The boid whose neighbors are to be found.
 * @param neighbors Output array to store the closest neighbors.
 */
void boid_behavior_find_neighbors(
    const boid           subject_boid, 
          boid_neighbor* neighbors
)
{
    // Initialize neighbor array to safe defaults.
    for (size_t i = 0; i < BOID_NEIGHBORHOOD_SIZE; ++i)
    {
        neighbors[i].distance = 0.0f;
        neighbors[i].index = 0;
    }

    boid_neighbor all_possible_neighbors[BOID_COUNT];

    // Calculate distance from subject to all boids.
    for (size_t i = 0; i < BOID_COUNT; ++i)
    {
        const boid other = array_boids_previous[i];

        all_possible_neighbors[i].distance = 
            boid_physics_distance_of_boids(
                subject_boid, 
                other
            );
        all_possible_neighbors[i].index    = i;
    }

    // Sort all by distance.
    sort_all_neighbors(all_possible_neighbors);

    // Pick closest neighbors skipping the boid itself at index 0.
    for (size_t i = 0; i < BOID_NEIGHBORHOOD_SIZE; ++i)
    {
        neighbors[i] = all_possible_neighbors[i + 1];
    }
}

/**
 * @brief Check if a boid is close enough to a wall to trigger wall avoidance.
 *
 * @param subject_boid The boid to check.
 * @return int Returns 1 if wall avoidance should trigger, otherwise 0.
 */
int boid_behavior_environment_trigger(boid subject_boid)
{
    return boid_physics_min_distance_to_environment(subject_boid) < 
           BOID_TRIGGER_ENVIRONMENT;
}

/**
 * @brief Apply repulsion to a boid to steer it away from nearby walls.
 *
 * Modifies the boid's direction vector to
 * avoid collisions with the environment.
 *
 * @param subject_boid Pointer to the boid to update.
 */
void boid_behavior_handle_environment(boid* subject_boid)
{
    vector_3d repulsion_direction = { 0.0f, 0.0f, 0.0f };
    boid_physics_target_direction_environment(
        *subject_boid, 
        &repulsion_direction
    );

    for (int i = 0; i < 3; ++i)
    {
        subject_boid->direction[i] += 
            repulsion_direction[i] * 
            BOID_STRENGTH_ENVIRONMENT;
    }
    geometry_normalize_vector(subject_boid->direction);
}


/**
 * @brief Apply alignment behavior steering
 *        a boid to match neighbors' directions.
 *
 * @param subject_boid Pointer to the boid to update.
 * @param neighbors Array of neighbor boids for alignment reference.
 */
static void handle_neighbors_align(
          boid*          subject_boid, 
    const boid_neighbor* neighbors
)
{
    vector_3d alignment_direction = { 0.0f, 0.0f, 0.0f };
    boid_physics_target_direction_neighbor_alignment(
        *subject_boid, 
         neighbors, 
        &alignment_direction
    );

    for (int i = 0; i < 3; ++i)
    {
        subject_boid->direction[i] += 
            alignment_direction[i] * 
            BOID_STRENGTH_ALIGNMENT;
    }
    geometry_normalize_vector(subject_boid->direction);
}

/**
 * @brief Apply separation behavior to steer a boid
 *        away from its closest neighbor if too close.
 *
 * @param subject_boid Pointer to the boid to update.
 * @param closest_neighbor The nearest neighbor boid to consider for separation.
 */
static void handle_neighbors_separate(
          boid*         subject_boid, 
    const boid_neighbor closest_neighbor)
{
    const boid    neighbor = array_boids_previous[closest_neighbor.index];
    const GLfloat distance = 
        boid_physics_distance_of_boids(
            *subject_boid, 
            neighbor
        );

    if (distance < BOID_TRIGGER_SEPARATE)
    {
        vector_3d separation_vector = {
            subject_boid->position[0] - neighbor.position[0],
            subject_boid->position[1] - neighbor.position[1],
            subject_boid->position[2] - neighbor.position[2]
        };
        geometry_normalize_vector(separation_vector);

        GLfloat repulsion_strength = 
            1.0f                              / 
            (distance * distance + 0.000001f) * 
            BOID_STRENGTH_SEPARATE;

        for (int i = 0; i < 3; ++i)
        {
            subject_boid->direction[i] += 
                separation_vector[i] * 
                repulsion_strength;
        }
        geometry_normalize_vector(subject_boid->direction);
    }
}

/**
 * @brief Apply cohesion behavior to steer a boid
 *        toward the average position of its neighbors.
 *
 * @param subject_boid Pointer to the boid to update.
 * @param neighbors Array of neighbor boids for cohesion reference.
 */
static void handle_neighbors_cohere(
          boid*          subject_boid, 
    const boid_neighbor* neighbors
)
{
    vector_3d cohesion_direction = { 0.0f, 0.0f, 0.0f };
    boid_physics_target_direction_neighbor_cohesion(
        *subject_boid, 
         neighbors, 
        &cohesion_direction
    );

    for (int i = 0; i < 3; ++i)
    {
        subject_boid->direction[i] += 
            cohesion_direction[i] * 
            BOID_STRENGTH_COHESION;
    }
    geometry_normalize_vector(subject_boid->direction);
}

/**
 * @brief Handle flocking behavior by applying
 *        alignment, separation, and cohesion.
 *
 * Finds neighbors and applies all three
 * behaviors to update the boid's direction.
 *
 * @param subject_boid Pointer to the boid to update.
 */
void boid_behavior_handle_neighbors(boid* subject_boid)
{
    boid_neighbor neighbors[BOID_NEIGHBORHOOD_SIZE];
    boid_behavior_find_neighbors(*subject_boid, neighbors);

    handle_neighbors_align(subject_boid, neighbors);
    handle_neighbors_separate(subject_boid, neighbors[0]);
    handle_neighbors_cohere(subject_boid, neighbors);
}
