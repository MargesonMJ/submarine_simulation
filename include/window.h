/**
 * @file window.h
 * @brief Handles window initialization and user input sensitivity.
 */


#pragma once


#include <GL/freeglut.h>


#define DEFAULT_WINDOW_WIDTH 1280  // pixels
#define DEFAULT_WINDOW_HEIGHT 720  // pixels

#define DEFAULT_WINDOW_MOUSE_SENSITIVITY 0.005f  // default mouse sensitivity for camera


/**
 * @brief Stores global window settings.
 */
typedef struct {
    GLint   width;             // window width.
    GLint   height;            // window height.
    GLint   mouse_x;           // last mouse x-coordinate.
    GLint   mouse_y;           // last mouse y-coordinate.
    GLfloat mouse_sensitivity; // mouse movement sensitivity factor.
} Window;


extern Window main_window;     // global window configuration and state.
extern int    full_screen_on;  // 1 indicates fullscreen is enabled, 0 indicates disabled.


/**
 * @brief Initializes the main window and sets up GLUT callbacks.
 *
 * @param argc Argument count from main().
 * @param argv Argument vector from main().
 */
void window_initialize(int argc, char** argv);
