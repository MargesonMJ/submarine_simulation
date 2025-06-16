/**
 * @file glut_callbacks.c
 * @brief Implements GLUT callbacks for rendering,
 *        input handling, and simulation updates.
 *
 * These callbacks manage user input (keyboard and mouse), viewport
 * resizing, display rendering, and the update loop for dynamic
 * elements like the submarine, water, and boids.
 */


#include "glut_callbacks.h"

#include "boids/boids.h"
#include "camera.h"
#include "renderer.h"
#include "submarine.h"
#include "water.h"
#include "window.h"


 /**
  * @brief GLUT display callback.
  *
  * Clears the buffers, sets up the camera view with gluLookAt,
  * configures lighting, calls the renderer to draw the scene,
  * and swaps buffers to display the rendered frame.
  */
void callback_display(void)
{
    // Clear color and depth buffers to prepare for new frame rendering.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the model-view matrix.
    glLoadIdentity();

    // Setup camera view based on current camera position and look_at target.
    gluLookAt(
        main_camera.position[0], 
        main_camera.position[1], 
        main_camera.position[2],
        main_camera.look_at[0], 
        main_camera.look_at[1], 
        main_camera.look_at[2],
        0.0, 
        1.0, 
        0.0
    );

    // Set light position for the scene.
    const GLfloat light_position[4] = { 0.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Call the renderer to draw all scene objects.
    renderer_draw();

    // Swap front and back buffers to display the rendered image.
    glutSwapBuffers();
}

/**
 * @brief GLUT reshape callback.
 *
 * Updates the OpenGL viewport and projection matrix whenever
 * the window size changes to maintain correct aspect ratio.
 *
 * @param width  New window width.
 * @param height New window height.
 */
void callback_reshape(int width, int height)
{
    // Set viewport to cover the entire new window.
    glViewport(0, 0, width, height);

    // Switch to projection matrix mode to update projection.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate the aspect ratio to avoid distortion.
    const double aspect = (double)width / (double)height;

    // Setup perspective projection with current
    // camera FOV and near/far clipping planes.
    gluPerspective(
        main_camera.fov, 
        aspect, 
        DEFAULT_CAMERA_NEAR_PLANE, 
        DEFAULT_CAMERA_FAR_PLANE
    );

    // Switch back to model-view matrix mode for further transformations.
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief GLUT idle callback.
 *
 * Called when the application is idle. Used here as the main update loop.
 * Updates the water simulation, submarine state, camera, and boids,
 * then triggers a redisplay to refresh the screen.
 */
void callback_idle(void)
{
    water_update();
    submarine_update();
    camera_update();
    boids_update();

    // Request GLUT to redraw the window.
    glutPostRedisplay();
}

/**
 * @brief GLUT passive mouse motion callback.
 *
 * Called when the mouse moves inside the window without any
 * buttons pressed. Updates the camera's orientation angles
 * (theta and phi) based on mouse movement, applying sensitivity
 * scaling and clamping vertical rotation to avoid flipping.
 *
 * @param x Current x-coordinate of the mouse.
 * @param y Current y-coordinate of the mouse.
 */
void callback_passive_motion(int x, int y)
{
    // Initialize stored mouse position if not already set.
    if (main_window.mouse_x == -1 || main_window.mouse_y == -1)
    {
        main_window.mouse_x = x;
        main_window.mouse_y = y;
        return;
    }

    // Calculate mouse movement delta since last callback.
    GLint mouse_delta_x = x - main_window.mouse_x;
    GLint mouse_delta_y = y - main_window.mouse_y;

    // Update camera horizontal angle (theta)
    // based on horizontal mouse movement.
    main_camera.theta += (GLfloat)mouse_delta_x * main_window.mouse_sensitivity;

    // Update camera vertical angle (phi) based on vertical
    // mouse movement, inverted for natural feel.
    main_camera.phi -= (GLfloat)mouse_delta_y * main_window.mouse_sensitivity;

    // Clamp phi to just under +- 90 degrees to prevent flipping.
    if (main_camera.phi > PI / 2 - 0.01f)
    {
        main_camera.phi = PI / 2 - 0.01f;
    }
    else if (main_camera.phi < -PI / 2 + 0.01f)
    {
        main_camera.phi = -PI / 2 + 0.01f;
    }

    // Update stored mouse position.
    main_window.mouse_x = x;
    main_window.mouse_y = y;
}

/**
 * @brief GLUT keyboard key release callback.
 *
 * Called when an ASCII key is released.
 * Used here to stop submarine movement in the corresponding direction
 * if the released key matches a movement key.
 *
 * @param key Released key character.
 * @param x   Mouse x-coordinate at release.
 * @param y   Mouse y-coordinate at release.
 */
void callback_keyboard_up(unsigned char key, int x, int y)
{
    // Stop movement in the relevant direction when key released.
    switch (key)
    {
    case 'w':
        if (object_submarine.direction[2] > 0.0f)
        {
            object_submarine.direction[2] = 0.0f;
        }
        break;

    case 's':
        if (object_submarine.direction[2] < 0.0f)
        {
            object_submarine.direction[2] = 0.0f;
        }
        break;

    case 'a':
        if (object_submarine.direction[0] > 0.0f)
        {
            object_submarine.direction[0] = 0.0f;
        }
        break;

    case 'd':
        if (object_submarine.direction[0] < 0.0f)
        {
            object_submarine.direction[0] = 0.0f;
        }
        break;
    }

    // If no directional input remains, stop submarine movement.
    if (geometry_is_zero_vector(object_submarine.direction))
    {
        object_submarine.speed = 0.0f;
    }
}

/**
 * @brief GLUT keyboard key press callback.
 *
 * Called when an ASCII key is pressed.
 * Handles submarine directional movement, toggling rendering modes,
 * fullscreen/windowed mode, fog, and quitting the application.
 *
 * @param key Pressed key character.
 * @param x   Mouse x-coordinate at press.
 * @param y   Mouse y-coordinate at press.
 */
void callback_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        // Move forward along the z-axis.
        object_submarine.direction[2] = 1.0f;
        break;

    case 's':
        // Move backward along the z-axis.
        object_submarine.direction[2] = -1.0f;
        break;

    case 'a':
        // Move left along the x-axis.
        object_submarine.direction[0] = 1.0f;
        break;

    case 'd':
        // Move right along the x-axis.
        object_submarine.direction[0] = -1.0f;
        break;

    case 'u':
        // Toggle wireframe rendering mode on/off.
        if (wire_frame_on)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Solid fill
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
        }
        wire_frame_on = !wire_frame_on;
        break;

    case 'f':
        // Toggle fullscreen/windowed mode.
        if (full_screen_on)
        {
            // Switch to windowed mode with default
            // dimensions at top-left corner.
            glutReshapeWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
            glutPositionWindow(0, 0);
        }
        else
        {
            // Enter fullscreen mode.
            glutFullScreen();
        }
        full_screen_on = !full_screen_on;
        break;

    case 'b':
        // Toggle OpenGL fog effect.
        if (fog_on)
        {
            glDisable(GL_FOG);
        }
        else
        {
            glEnable(GL_FOG);
        }
        fog_on = !fog_on;
        break;

    case 'q':
        // Quit the application cleanly.
        glutExit();
        break;

    default:
        // Ignore other keys.
        break;
    }

    // If any movement direction is active, set submarine speed to default.
    if (!geometry_is_zero_vector(object_submarine.direction))
    {
        object_submarine.speed = SUBMARINE_SPEED;
    }
}

/**
 * @brief GLUT special key release callback.
 *
 * Called when a special key (e.g., arrow keys) is released.
 * Stops vertical submarine movement corresponding to up/down keys.
 *
 * @param key Released special key.
 * @param x   Mouse x-coordinate at release.
 * @param y   Mouse y-coordinate at release.
 */
void callback_special_up(int key, int x, int y)
{
    if (key == GLUT_KEY_UP &&
        object_submarine.direction[1] > 0.0f)
    {
        object_submarine.direction[1] = 0.0f;
    }
    else if (key == GLUT_KEY_DOWN &&
        object_submarine.direction[1] < 0.0f)
    {
        object_submarine.direction[1] = 0.0f;
    }

    // If no directional input remains, stop submarine movement.
    if (geometry_is_zero_vector(object_submarine.direction))
    {
        object_submarine.speed = 0.0f;
    }
}

/**
 * @brief GLUT special key press callback.
 *
 * Called when a special key (e.g., arrow keys) is pressed.
 * Controls vertical movement of the submarine (up/down).
 *
 * @param key Pressed special key.
 * @param x   Mouse x-coordinate at press.
 * @param y   Mouse y-coordinate at press.
 */
void callback_special(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        // Move submarine up along the y-axis.
        object_submarine.direction[1] = 1.0f;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        // Move submarine down along the y-axis.
        object_submarine.direction[1] = -1.0f;
    }

    // If any movement direction is active, set submarine speed to default.
    if (!geometry_is_zero_vector(object_submarine.direction))
    {
        object_submarine.speed = SUBMARINE_SPEED;
    }
}
