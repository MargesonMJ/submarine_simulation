/**
 * @file window.c
 * @brief Implementation for window and GLUT initialization.
 */


#include "window.h"
#include "glut_callbacks.h"


// Global instance of the window settings.
Window main_window = {
    DEFAULT_WINDOW_WIDTH,
    DEFAULT_WINDOW_HEIGHT,
    -1,
    -1,
    DEFAULT_WINDOW_MOUSE_SENSITIVITY
};

int full_screen_on = 0;


/**
 * @brief Sets up the OpenGL window and registers GLUT callbacks.
 *
 * @param argc Argument count from main().
 * @param argv Argument vector from main().
 */
void window_initialize(int argc, char** argv)
{
    // Initialize FreeGLUT toolkit.
    glutInit(&argc, argv);

    // Initialize FreeGLUT window.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  // double buffering, RGBA colors, 3D.
    glutInitWindowSize(main_window.width, main_window.height);
    glutCreateWindow("Submarine Simulator - Matthew Margeson");

    // Assign window callbacks for user interaction.
    glutDisplayFunc(callback_display);
    glutReshapeFunc(callback_reshape);
    glutIdleFunc(callback_idle);
    glutPassiveMotionFunc(callback_passive_motion);
    glutKeyboardUpFunc(callback_keyboard_up);
    glutKeyboardFunc(callback_keyboard);
    glutSpecialUpFunc(callback_special_up);
    glutSpecialFunc(callback_special);
}
