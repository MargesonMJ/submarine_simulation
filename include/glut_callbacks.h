/**
 * @file glut_callbacks.h
 * @brief Declares GLUT callback functions for
 *        input handling, rendering, and updates.
 *
 * These callbacks handle events such as drawing the screen,
 * resizing the window, responding to keyboard and special
 * keys, mouse movement, and application idle updates.
 */


#pragma once


 /**
  * @brief Called by GLUT when the window needs to be redrawn.
  *
  * This function sets up the camera, lighting,
  * and calls the renderer to draw the scene.
  */
void callback_display(void);

/**
 * @brief Called when the GLUT window is resized.
 *
 * Updates the OpenGL viewport and projection
 * matrix to maintain correct aspect ratio.
 *
 * @param width  New width of the window in pixels.
 * @param height New height of the window in pixels.
 */
void callback_reshape(int width, int height);

/**
 * @brief Called when the application is idle.
 *
 * This serves as the main update loop. It updates
 * simulation elements such as water, submarine,
 * camera, and boids, then triggers a redraw.
 */
void callback_idle(void);

/**
 * @brief Called when the mouse moves within the
 *        window without clicking any buttons.
 *
 * Used to update the camera direction based on mouse movement.
 *
 * @param x Current x-coordinate of the mouse.
 * @param y Current y-coordinate of the mouse.
 */
void callback_passive_motion(int x, int y);

/**
 * @brief Called when an ASCII key is released.
 *
 * Used to stop submarine movement when a movement key is released.
 *
 * @param key Released key.
 * @param x   Mouse x-coordinate at the time of key release.
 * @param y   Mouse y-coordinate at the time of key release.
 */
void callback_keyboard_up(unsigned char key, int x, int y);

/**
 * @brief Called when an ASCII key is pressed.
 *
 * Handles submarine movement and toggles for rendering
 *         modes, fullscreen, fog, and exiting.
 *
 * @param key Pressed key.
 * @param x   Mouse x-coordinate at the time of key press.
 * @param y   Mouse y-coordinate at the time of key press.
 */
void callback_keyboard(unsigned char key, int x, int y);

/**
 * @brief Called when a special key (e.g., arrow keys) is released.
 *
 * Used to stop vertical movement of the submarine.
 *
 * @param key Released special key.
 * @param x   Mouse x-coordinate at the time of key release.
 * @param y   Mouse y-coordinate at the time of key release.
 */
void callback_special_up(int key, int x, int y);

/**
 * @brief Called when a special key (e.g., arrow keys) is pressed.
 *
 * Controls vertical movement of the submarine.
 *
 * @param key Pressed special key.
 * @param x   Mouse x-coordinate at the time of key press.
 * @param y   Mouse y-coordinate at the time of key press.
 */
void callback_special(int key, int x, int y);
