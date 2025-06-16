/**
 * @file renderer.c
 * @brief Implementation of rendering logic, scene setup, and object drawing.
 */


#include "renderer.h"

#include "boids/boids.h"
#include "camera.h"
#include "coral.h"
#include "environment.h"
#include "GL/freeglut.h"
#include "window.h"
#include "lighting.h"
#include "submarine.h"
#include "water.h"


int fog_on        = 0;  // starts as zero until fog is initialized.
int wire_frame_on = 0;  // starts as zero until wire_frame is turned on by user.


/**
 * @brief Initializes OpenGL state and all scene components.
 */
void renderer_initialize(void)
{
	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
	// Enable texture mapping.
	glEnable(GL_TEXTURE_2D);
	// Enable texture mode.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Enable the unit vector normals.
	glEnable(GL_NORMALIZE);
	// Enable alpha blending.
    glEnable(GL_BLEND);
	// Use alpha blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable smooth lighting.
	glShadeModel(GL_SMOOTH);

	// Initialize fog for underwater appearance.
	glEnable(GL_FOG);
	fog_on = 1;
	const GLfloat fog_color[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.1f);

	// Change into projection mode so that we can change the camera properties.
	glMatrixMode(GL_PROJECTION);

	// Load the identity matrix into projection matrix.
	glLoadIdentity();

    const GLdouble aspect = 
		(double)main_window.width / (double)main_window.height;

	gluPerspective(
		DEFAULT_CAMERA_FOV, 
		aspect, 
		DEFAULT_CAMERA_NEAR_PLANE, 
		DEFAULT_CAMERA_FAR_PLANE
    );

	// Change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);

	environment_initialize();

	water_initialize();

	// Initialize scene objects.
	submarine_initialize();

	coral_initialize();

	boids_initialize();
}

/**
 * @brief Draws 3D origin axis lines and a small sphere at the origin.
 */
void draw_origin(void)
{
	const color diffuse_red   = { 1.0f, 0.0f, 0.0f, 1.0f };  // x-axis
	const color diffuse_green = { 0.0f, 1.0f, 0.0f, 1.0f };  // y-axis
	const color diffuse_blue  = { 0.0f, 0.0f, 1.0f, 1.0f };  // z-axis
	const color diffuse_white = { 1.0f, 1.0f, 1.0f, 1.0f };  // centre-sphere quadric.

	const color emission_red   = { 1.0f, 0.0f, 0.0f, 0.5f };
	const color emission_green = { 0.0f, 1.0f, 0.0f, 0.5f };
	const color emission_blue  = { 0.0f, 0.0f, 1.0f, 0.5f };
	const color emission_white = { 1.0f, 1.0f, 1.0f, 0.5f };

	const point_3d point_center = { 0.0f, 0.0f, 0.0f };
	const GLfloat  origin_size  = 1.0f;

	const GLfloat axis_width = 5.0f;
	glLineWidth(axis_width);

	glPushMatrix();
	    glBegin(GL_LINES);  // x-axis - red.
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_red);
			glMaterialfv(GL_FRONT, GL_EMISSION, emission_red);
		    glVertex3fv(point_center);
		    glVertex3f(origin_size, 0.0f, 0.0f);
	    glEnd();
		glBegin(GL_LINES);  // y-axis - green.
		    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_green);
			glMaterialfv(GL_FRONT, GL_EMISSION, emission_green);
		    glVertex3fv(point_center);
		    glVertex3f(0.0f, origin_size, 0.0f);
		glEnd();
		glBegin(GL_LINES);  // z-axis - blue.
		    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_blue);
			glMaterialfv(GL_FRONT, GL_EMISSION, emission_blue);
		    glVertex3fv(point_center);
			glVertex3f(0.0f, 0.0f, origin_size);
		glEnd();
        // Origin sphere.
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_white);
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_white);
		gluSphere(quadric_origin_sphere, origin_size / 10, 20, 20);
	glPopMatrix();

	const color emission_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_zero);
	const GLfloat default_line_width = 1.0f;
	glLineWidth(default_line_width);
}

/**
 * @brief Draws the floor and cylindrical wall environment.
 */
void draw_environment(void)
{
	// Floor.
	const color diffuse_disk      = { 0.9f, 0.6f, 0.3f, 1.0f };
	const color emission_disk     = { 0.3f, 0.2f, 0.1f, 1.0f };
	// Walls.
	const color diffuse_cylinder  = { 0.5f, 0.5f, 0.5f, 1.0f };
	const color emission_cylinder = { 1.0f, 1.0f, 1.0f, 1.0f };
	// Default.
	const color emission_zero     = { 0.0f, 0.0f, 0.0f, 0.0f };

	glBindTexture(GL_TEXTURE_2D, texture_id_environment);

	glPushMatrix();
	    glTranslatef(0.0f, -1.0f, 0.0f);
	    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		// Floor - disk.
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_disk);
	    glMaterialfv(GL_FRONT, GL_EMISSION, emission_disk);
	    gluDisk(quadric_environment, 0.0, ENVIRONMENT_RADIUS_XZ + 1, 20, 20);
		// Walls - cylinder.
		glTranslatef(0.0f, -1.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_cylinder);
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_cylinder);
		gluCylinder(
			quadric_environment, 
			ENVIRONMENT_RADIUS_XZ, 
			ENVIRONMENT_RADIUS_XZ, 
			ENVIRONMENT_HEIGHT + 1, 
			20, 
			20
		);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_zero);  // reset emission.
	glBindTexture(GL_TEXTURE_2D, 0);                     // unbind current texture to avoid re-use.
}

/**
 * @brief Draws a grid of water vertices at the water surface.
 */
void draw_water(void)
{
	const point_3d water_position = { 0.0f, 10.0f, 0.0f };

	glPushMatrix();
	glTranslatef(water_position[0], water_position[1], water_position[2]);
	for (int i = 0; i < WATER_GRID_SIZE; ++i)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= WATER_GRID_SIZE; ++j)
		{
			glVertex3fv(water_vertices[i][j]);
			glVertex3fv(water_vertices[i + 1][j]);
		}
		glEnd();
	}
	glPopMatrix();
}

/**
 * @brief Renders a mesh using its faces, vertices, and normals.
 *
 * @param mesh The mesh object to draw.
 */
void draw_mesh(const mesh mesh)
{
	for (int i = 0; i < mesh.face_count; ++i)
	{
		const mesh_face face = mesh.faces[i];

		glBegin(GL_TRIANGLES);  // draw face of 3 normals, 3 vertices.
		    glNormal3f(
			    mesh.normals[face.normal_numbers[0] - 1][0],
			    mesh.normals[face.normal_numbers[0] - 1][1],
			    mesh.normals[face.normal_numbers[0] - 1][2]
			);
		    glVertex3f(
			    mesh.vertices[face.vertex_numbers[0] - 1][0],
			    mesh.vertices[face.vertex_numbers[0] - 1][1],
			    mesh.vertices[face.vertex_numbers[0] - 1][2]
			);
		    glNormal3f(
			    mesh.normals[face.normal_numbers[1] - 1][0],
			    mesh.normals[face.normal_numbers[1] - 1][1],
			    mesh.normals[face.normal_numbers[1] - 1][2]
			);
		    glVertex3f(
			    mesh.vertices[face.vertex_numbers[1] - 1][0],
			    mesh.vertices[face.vertex_numbers[1] - 1][1],
			    mesh.vertices[face.vertex_numbers[1] - 1][2]
			);
		    glNormal3f(
			    mesh.normals[face.normal_numbers[2] - 1][0],
			    mesh.normals[face.normal_numbers[2] - 1][1],
			    mesh.normals[face.normal_numbers[2] - 1][2]
			);
		    glVertex3f(
			    mesh.vertices[face.vertex_numbers[2] - 1][0],
			    mesh.vertices[face.vertex_numbers[2] - 1][1],
			    mesh.vertices[face.vertex_numbers[2] - 1][2]
			);
		glEnd();
	}
}


/**
 * @brief Draws a scene object with transformation and lighting applied.
 *
 * @param object The scene object to render.
 */
void draw_scene_object(const scene_object object)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, object.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, object.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, object.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, object.shine);

	geometry_normalize_vector(object.direction);  // forward vector.

	glPushMatrix();
	    glTranslatef(
			object.position[0], 
			object.position[1], 
			object.position[2]
		);
		glRotatef(
			geometry_calculate_yaw_degree(object.direction), 
			0.0f, 
			1.0f, 
			0.0f
		);
	    glRotatef(
			-geometry_calculate_pitch_degree(object.direction), 
			1.0f, 
			0.0f, 
			0.0f
		);
		glRotatef(object.rotation, 0.0f, 1.0f, 0.0f);  // used when object is facing improper direction (specifically the submarine).

	    glScalef(object.scale, object.scale, object.scale);

		draw_mesh(object.mesh);
	glPopMatrix();

	const color color_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT,   color_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_zero);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  color_zero);
	glMaterialfv(GL_FRONT, GL_SHININESS, color_zero);
}

/**
 * @brief Draws the submarine model.
 */
void draw_submarine(void)
{
	draw_scene_object(object_submarine);
}

/**
 * @brief Draws all coral scene objects.
 */
void draw_coral(void)
{
    for (int i = 0; i < CORAL_COUNT; ++i)
    {
		draw_scene_object(objects_coral[i]);
    }
}


/**
 * @brief Draws all boid entities as simple triangular 3D shapes.
 */
void draw_boids(void)
{
	point_3d apex         = {  0.0f,       0.0f,       BOID_APEX };
	point_3d top_left     = {  BOID_BASE,  BOID_BASE, -BOID_APEX };
	point_3d top_right    = { -BOID_BASE,  BOID_BASE, -BOID_APEX };
	point_3d bottom_left  = {  BOID_BASE, -BOID_BASE, -BOID_APEX };
	point_3d bottom_right = { -BOID_BASE, -BOID_BASE, -BOID_APEX };

	vector_3d normal_top        = { 0.0f, 0.0f, 0.0f };
    geometry_calculate_normal(apex, top_left, top_right, normal_top);

	vector_3d normal_left       = { 0.0f, 0.0f, 0.0f };
	geometry_calculate_normal(apex, bottom_left, top_left, normal_left);

	vector_3d normal_bottom     = { 0.0f, 0.0f, 0.0f };
	geometry_calculate_normal(apex, bottom_right, bottom_left, normal_bottom);

	vector_3d normal_right      = { 0.0f, 0.0f, 0.0f };
	geometry_calculate_normal(apex, bottom_right, top_right, normal_right);

	vector_3d normal_base_left  = { 0.0f, 0.0f, 0.0f };
	geometry_calculate_normal(
		top_left, 
		bottom_left, 
		top_right, 
		normal_base_left
	);

	vector_3d normal_base_right = { 0.0f, 0.0f, 0.0f };
	geometry_calculate_normal(
		top_right, 
		bottom_left, 
		bottom_right, 
		normal_base_right
	);

	color ambient  = { BOID_AMBIENT,  BOID_AMBIENT,  BOID_AMBIENT,  1.0f };
	color diffuse  = { 0.0f,          BOID_DIFFUSE,  BOID_DIFFUSE,  1.0f };
	color specular = { BOID_SPECULAR, BOID_SPECULAR, BOID_SPECULAR, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
	glMaterialf (GL_FRONT, GL_SHININESS, BOID_SHINE);

    for (int i = 0; i < BOID_COUNT; ++i)
    {
		const boid subject_boid = array_boids_current[i];

        glPushMatrix();
		    glTranslatef(
				subject_boid.position[0], 
				subject_boid.position[1], 
				subject_boid.position[2]
			);
			glRotatef(
				geometry_calculate_yaw_degree(subject_boid.direction), 
				0.0f, 
				1.0f, 
				0.0f
			);
			glRotatef(
				-geometry_calculate_pitch_degree(subject_boid.direction), 
				1.0f, 
				0.0f, 
				0.0f
			);
			glScalef(BOID_SCALE, BOID_SCALE, BOID_SCALE);

			glBegin(GL_TRIANGLES);
			    // Top face
			    glNormal3fv(normal_top);
			    glVertex3fv(apex);
			    glVertex3fv(top_left);
			    glVertex3fv(top_right);

			    // Left face
			    glNormal3fv(normal_left);
			    glVertex3fv(apex);
			    glVertex3fv(bottom_left);
			    glVertex3fv(top_left);

			    // Bottom face
			    glNormal3fv(normal_bottom);
			    glVertex3fv(apex);
			    glVertex3fv(bottom_left);
			    glVertex3fv(bottom_right);

			    // Right face
			    glNormal3fv(normal_right);
			    glVertex3fv(apex);
			    glVertex3fv(bottom_right);
			    glVertex3fv(top_right);

			    // Base left face
			    glNormal3fv(normal_base_left);
			    glVertex3fv(top_left);
			    glVertex3fv(bottom_left);
			    glVertex3fv(top_right);

			    // Base right face
			    glNormal3fv(normal_base_right);
			    glVertex3fv(top_right);
			    glVertex3fv(bottom_left);
			    glVertex3fv(bottom_right);
			glEnd();
		glPopMatrix();
    }

	const color color_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color_zero);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_zero);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_zero);
	glMaterialfv(GL_FRONT, GL_SHININESS, color_zero);
}

/**
 * @brief Calls all drawing functions to render the full scene.
 */
void renderer_draw(void)
{
	draw_origin();
	draw_environment();
	draw_water();
	draw_submarine();
	draw_coral();
	draw_boids();
}

/**
 * @brief Frees renderer resources.
 */
void renderer_clean_up(void)
{
	submarine_cleanup();
	coral_cleanup();
}
