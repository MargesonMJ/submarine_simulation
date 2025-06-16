/**
 * @file renderer.h
 * @brief Renderer interface for scene initialization, drawing, and cleanup.
 */


#pragma once


extern int fog_on;         // 1 indicates fog enabled, 0 disabled.
extern int wire_frame_on;  // 1 indicates wireframe rendering enabled, 0 disabled.


/**
 * @brief Initializes rendering state and scene objects.
 */
void renderer_initialize(void);

/**
 * @brief Renders all elements of the scene.
 */
void renderer_draw(void);

/**
 * @brief Cleans up renderer-specific resources.
 */
void renderer_clean_up(void);
