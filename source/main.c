/**
 * @file main.c
 * @brief Entry point of the simulation program.
 */


#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "renderer.h"
#include "window.h"
#include "lighting.h"


static void print_controls_to_console(void);  // forward declaration.


/**
 * @brief Main function initializing the simulation
 *        and entering the rendering loop.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit code.
 */
int main(int argc, char** argv)
{
	window_initialize(argc, argv);
	lighting_initialize();
    renderer_initialize();

	print_controls_to_console();

	glutMainLoop();  // Enter perpetual rendering loop.

	renderer_clean_up();

	return 0;
}

/**
 * Prints the user controls for the OpenGL application
 * to the system console. Called once at startup.
 */
static void print_controls_to_console(void)
{
	// Print the scene controls to the console.
	printf("Scene Controls\n");
	printf("-------------------\n");
	printf("u:\t\t\ttoggle wire frame mode\n");
	printf("b:\t\t\ttoggle fog\n");
	printf("f:\t\t\ttoggle full screen window\n\n");

	// Print the camera controls to the console.
	printf("Camera Controls\n");
	printf("-------------------\n");
	printf("W:\t\t\tMove forward\n");
	printf("S\t\t\tMove backwards\n");
	printf("A:\t\t\tMove right\n");
	printf("D\t\t\tMove left\n");
	printf("Up Arrow:\t\tMove up\n");
	printf("Down Arrow:\t\tMove down\n");
	printf("Mouse to the right:\trotates the camera to the right of the submarine\n");
	printf("Mouse to the left:\trotates the camera to the left of the submarine\n");
	printf("Mouse upwards:\t\trotates the camera to the top of the submarine\n");
	printf("Mouse downwards:\trotates the camera to the bottom of the submarine\n");
}