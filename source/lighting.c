/**
 * @file lighting.c
 * @brief Scene lighting configuration for OpenGL.
 */


#include "lighting.h"


/**
 * @brief Configures ambient, diffuse, and specular lighting for the scene.
 */
void lighting_initialize(void)
{
	// Light color and intensity. Ambient will be zeroAmbient,
	const color light_diffuse        = { 0.9f, 0.9f, 0.9f, 1.0f };
	const color light_specular       = { 0.9f, 0.9f, 0.9f, 1.0f };
	const color light_ambient_global = { 0.2f, 0.2f, 0.2f, 1.0f };
	const color light_ambient_zero   = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Set the global ambient light level.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);

	// Define the color and intensity for light 0.
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_zero);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_specular);

	//Enable the lighting.
	glEnable(GL_LIGHTING);
	// Enable light 0.
	glEnable(GL_LIGHT0);
}
