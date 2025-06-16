/**
 * @file boid_physics.c
 * @brief Implements physics calculations for boids including
 *        distance computations, wall proximity detection,
 *        target rotation computations for wall avoidance and
 *        neighbor interactions, and position updates.
 */


#include "boids/boid_physics.h"

#include "boids/boid_behavior.h"
#include "environment.h"

#include <math.h>


/**
 * @brief Calculates and returns the Euclidean distance between two boids.
 *
 * @param b1 The first boid.
 * @param b2 The second boid.
 * @return GLfloat The distance between b1 and b2.
 */
GLfloat boid_physics_distance_of_boids(const boid b1, const boid b2)
{
    const GLfloat delta_x = b2.position[0] - b1.position[0];
    const GLfloat delta_y = b2.position[1] - b1.position[1];
    const GLfloat delta_z = b1.position[2] - b2.position[2];

    return sqrtf(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

/**
 * @brief Calculates the distance from the boid to
 *        the environment's cylindrical wall boundary.
 *
 * @param subject_boid The boid whose distance to the wall is calculated.
 * @return float Distance from the boid to the cylindrical wall.
 */
static float distance_to_wall(const boid subject_boid)
{
    const float distance_to_origin_xz = sqrtf(
        subject_boid.position[0] * subject_boid.position[0] +
        subject_boid.position[2] * subject_boid.position[2]
    );
    return ENVIRONMENT_RADIUS_XZ - distance_to_origin_xz;
}

/**
 * @brief Calculates the distance from the boid to
 *        the floor (lowest Y) of the environment.
 *
 * @param subject_boid The boid whose distance to the floor is calculated.
 * @return float Distance from the boid to the floor.
 */
static float distance_to_floor(const boid subject_boid)
{
    return subject_boid.position[1] - ENVIRONMENT_FLOOR_Y;
}

/**
 * @brief Calculates the distance from the boid to
 *        the ceiling (highest Y) of the environment.
 *
 * @param subject_boid The boid whose distance to the ceiling is calculated.
 * @return float Distance from the boid to the ceiling.
 */
static float distance_to_ceiling(const boid subject_boid)
{
    return ENVIRONMENT_HEIGHT - subject_boid.position[1];
}

/**
 * @brief Calculates the minimum distance from the
 *        boid to any edge of the environment.
 *
 * Compares distances to walls, floor, and ceiling to find the closest boundary.
 *
 * @param subject_boid The boid to measure distance for.
 * @return GLfloat The minimum distance to the environment boundary.
 */
GLfloat boid_physics_min_distance_to_environment(const boid subject_boid)
{
    float min_distance = distance_to_wall(subject_boid);
    min_distance = fminf(min_distance, distance_to_floor(subject_boid));
    min_distance = fminf(min_distance, distance_to_ceiling(subject_boid));
    return min_distance;
}

/**
 * @brief Computes the target direction for the boid
 *        to avoid walls and environment edges.
 *
 * The repulsion strength is inversely proportional to the
 * squared distance from each boundary. The target_direction
 * vector is modified accordingly and then normalized.
 *
 * @param subject_boid The boid for which to calculate avoidance direction.
 * @param target_direction Pointer to a vector_3d to
 *                         store the resulting direction.
 */
void boid_physics_target_direction_environment(
    const boid       subject_boid, 
          vector_3d* target_direction
)
{
    const float wall_distance = distance_to_wall(subject_boid);
    if (wall_distance < BOID_TRIGGER_ENVIRONMENT)
    {
        const float repulsion_strength =
            BOID_STRENGTH_ENVIRONMENT / 
            (wall_distance * wall_distance + 1e-6f);

        (*target_direction)[0] -= subject_boid.position[0] * repulsion_strength;
        (*target_direction)[2] -= subject_boid.position[2] * repulsion_strength;
    }

    const float floor_distance = distance_to_floor(subject_boid);
    if (floor_distance < BOID_TRIGGER_ENVIRONMENT)
    {
        const float repulsion_strength = 
            BOID_STRENGTH_ENVIRONMENT / 
            (floor_distance * floor_distance + 1e-6f);

        (*target_direction)[1] += repulsion_strength;
    }

    const float ceiling_distance = distance_to_ceiling(subject_boid);
    if (ceiling_distance < BOID_TRIGGER_ENVIRONMENT)
    {
        const float repulsion_strength = 
            BOID_STRENGTH_ENVIRONMENT / 
            (ceiling_distance * ceiling_distance + 1e-6f);

        (*target_direction)[1] -= repulsion_strength;
    }

    (*target_direction)[0] -= subject_boid.direction[0];
    (*target_direction)[1] -= subject_boid.direction[1];
    (*target_direction)[2] -= subject_boid.direction[2];
    geometry_normalize_vector(*target_direction);
}

/**
 * @brief Computes the target direction for the boid
 *        to align its heading with its neighbors.
 *
 * The average direction of neighbors is computed and the target direction
 * points from the boid's current direction toward this average.
 *
 * @param subject_boid The boid for which alignment is computed.
 * @param neighbors Array of neighbor boids.
 * @param target_direction Pointer to vector_3d to store the result.
 */
void boid_physics_target_direction_neighbor_alignment(
    const boid subject_boid,
    const boid_neighbor* neighbors,
    vector_3d* target_direction
)
{
    GLfloat sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;

    for (size_t i = 0; i < BOID_NEIGHBORHOOD_SIZE; ++i)
    {
        const size_t idx = neighbors[i].index;
        const boid neighbor = array_boids_previous[idx];

        sum_x += neighbor.direction[0];
        sum_y += neighbor.direction[1];
        sum_z += neighbor.direction[2];
    }

    GLfloat avg_x = sum_x / BOID_NEIGHBORHOOD_SIZE;
    GLfloat avg_y = sum_y / BOID_NEIGHBORHOOD_SIZE;
    GLfloat avg_z = sum_z / BOID_NEIGHBORHOOD_SIZE;

    (*target_direction)[0] = avg_x - subject_boid.direction[0];
    (*target_direction)[1] = avg_y - subject_boid.direction[1];
    (*target_direction)[2] = avg_z - subject_boid.direction[2];

    geometry_normalize_vector(*target_direction);
}

/**
 * @brief Computes the target direction for the boid to cohere toward neighbors.
 *
 * The average neighbor position is weighted inversely by squared distance,
 * producing a vector toward neighbors' center of mass.
 *
 * @param subject_boid The boid for which cohesion is computed.
 * @param neighbors Array of neighbor boids.
 * @param target_direction Pointer to vector_3d to store the result.
 */
void boid_physics_target_direction_neighbor_cohesion(
    const boid subject_boid,
    const boid_neighbor* neighbors,
    vector_3d* target_direction
)
{
    GLfloat sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f, total_weight = 0.0f;

    for (size_t i = 0; i < BOID_NEIGHBORHOOD_SIZE; ++i)
    {
        const size_t idx = neighbors[i].index;
        const boid neighbor = array_boids_previous[idx];

        GLfloat dist = boid_physics_distance_of_boids(subject_boid, neighbor);
        GLfloat weight = BOID_STRENGTH_COHESION / (dist * dist);

        sum_x += neighbor.position[0] * weight;
        sum_y += neighbor.position[1] * weight;
        sum_z += neighbor.position[2] * weight;
        total_weight += weight;
    }

    GLfloat avg_x = sum_x / total_weight;
    GLfloat avg_y = sum_y / total_weight;
    GLfloat avg_z = sum_z / total_weight;

    (*target_direction)[0] = avg_x - subject_boid.position[0];
    (*target_direction)[1] = avg_y - subject_boid.position[1];
    (*target_direction)[2] = avg_z - subject_boid.position[2];

    geometry_normalize_vector(*target_direction);
}

/**
 * @brief Updates the position of the boid by moving
 *        it along its direction vector scaled by speed.
 *
 * @param subject_boid Pointer to the boid to update.
 */
void boid_physics_update_position(boid* subject_boid)
{
    subject_boid->position[0] += subject_boid->direction[0] * BOID_SPEED;
    subject_boid->position[1] += subject_boid->direction[1] * BOID_SPEED;
    subject_boid->position[2] += subject_boid->direction[2] * BOID_SPEED;
}
