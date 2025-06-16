/**
 * @file boids.c
 * @brief Implements the boid flocking simulation logic,
 *        including initialization, behavior updates,
 *        environmental interaction, and physics-based movement.
 *
 * This file contains the main update loop for the boid simulation,
 * handling both environmental triggers and neighbor-based flocking behaviors.
 * It also manages the boids' position updates and state history.
 */


#include "boids/boids.h"

#include "boids/boid_behavior.h"
#include "boids/boid_physics.h"

#include "environment.h"

#include <math.h>


boid array_boids_current[BOID_COUNT];   // current boid states
boid array_boids_previous[BOID_COUNT];  // previous boid states


/**
 * @brief Initialize boids with randomized starting positions and directions.
 *
 * Positions are spread within a cubic volume above the "ground" and directions
 * are normalized to ensure consistent movement speed.
 */
void boids_initialize(void)
{
    for (int i = 0; i < BOID_COUNT; ++i)
    {
        boid* boid = &array_boids_current[i];

        // Randomize starting position in range X,Z [-4, 4] and Y [1, 8]
        boid->position[0] = ((GLfloat)rand() / (GLfloat)RAND_MAX) * 8.0f - 4.0f;
        boid->position[1] = (GLfloat)(rand() % 8) + 1.0f;
        boid->position[2] = ((GLfloat)rand() / (GLfloat)RAND_MAX) * 8.0f - 4.0f;

        // Randomize normalized starting direction vector
        boid->direction[0] = (GLfloat)rand() / (GLfloat)RAND_MAX;
        boid->direction[1] = (GLfloat)rand() / (GLfloat)RAND_MAX;
        boid->direction[2] = (GLfloat)rand() / (GLfloat)RAND_MAX;
        geometry_normalize_vector(boid->direction);
    }
}

/**
 * @brief Updates all boid behaviors and physics
 *        states for the current simulation step.
 *
 * Each boid is checked for proximity to environmental boundaries
 * or obstacles. If close, environment-specific behavior
 * adjustments are applied. Otherwise, neighbor-based flocking
 * behaviors are applied. Positions are updated accordingly.
 *
 * This function is internal to the module and not exposed publicly.
 */
static void update_boids_current(void)
{
    for (int i = 0; i < BOID_COUNT; ++i)
    {
        boid* boid = &array_boids_current[i];

        // Check if boid needs to respond to environment triggers
        if (boid_behavior_environment_trigger(*boid))
        {
            boid_behavior_handle_environment(boid);
        }
        else
        {
            // Apply flocking behavior based on neighbors
            boid_behavior_handle_neighbors(boid);
        }

        // Update position based on direction and speed
        boid_physics_update_position(boid);
    }
}

/**
 * @brief Copies the current boid states into the previous state array.
 *
 * This function stores the previous simulation step's boid data for use
 * in calculating smooth animations or physics.
 */
void update_boids_previous(void)
{
    for (int i = 0; i < BOID_COUNT; ++i)
    {
        array_boids_previous[i] = array_boids_current[i];
    }
}

/**
 * @brief Update the boids simulation by processing
 *        behavior, physics, and state history.
 *
 * This function calls internal updates for boid behavior and position, then
 * records the previous states for the next simulation frame.
 */
void boids_update(void)
{
    update_boids_current();
    update_boids_previous();
}
