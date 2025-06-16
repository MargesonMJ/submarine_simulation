/**
 * @file boids.h
 * @brief Definitions and functions for managing a
 *        flock of simulated boids in 3D space.
 *
 * Provides data structures and function declarations
 * for initializing, updating, and storing boid states
 * within the underwater environment simulation.
 */


#pragma once


#include "geometry.h"


#define BOID_COUNT 40      // number of boids
#define BOID_SPEED  0.01f  // default boid movement speed

#define BOID_NEIGHBORHOOD_SIZE 6  // number of neighbors a single boid contains

#define BOID_APEX      2.0f  // distance of boid apex vertex from center position.
#define BOID_BASE      1.0f  // distance of boid base vertices from center position.
#define BOID_AMBIENT   0.2f  // ambient material value
#define BOID_DIFFUSE   1.0f  // diffuse material value
#define BOID_SPECULAR  1.0f  // specular material value
#define BOID_SHINE    20.0f  // shine material value
#define BOID_SCALE     0.1f  // default scale of boid objects


/**
 * @brief Represents a single boid with position and direction in 3D space.
 */
typedef struct {
    point_3d  position;   // current 3D position of the boid
    vector_3d direction;  // current normalized movement direction
} boid;


extern boid array_boids_current[BOID_COUNT];   // global array of current boid 
extern boid array_boids_previous[BOID_COUNT];  // global array of previous boid states


/**
 * @brief Initialize all boids with random positions within the simulation
 *        bounds and assign them random normalized directions.
 *
 * This setup is called once at simulation start.
 */
void boids_initialize(void);

/**
 * @brief Advances the simulation by updating
 *        each boid's behavior and physics state.
 *
 * This function processes environmental interactions and neighbor influences,
 * then updates boid positions accordingly for the current frame.
 */
void boids_update(void);
