/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Virtual Camera - create and modify VIEW and PROJECTION matrices              |
| keyboard controls: W,S,A,D,left and right arrows                             |
\******************************************************************************/

#include "Object.h"
#include "maths_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\mat4x4.hpp>
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;
bool cam_moved;
float cam_speed = 3.0f; // 1 unit per second
float cam_yaw_speed = 50.0f; // 10 degrees per second
float cam_pos[] = { 0.0f, 0.0f, 10.0f }; // don't start at zero, or we will be too close
float cam_yaw = 0.0f;
float cam_yawvert = 0.0f;
double elapsed_seconds;
float scalex, scaley, scalez;

Object cubo;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void drawGround()
{
	// Draw ground
	int count = 0;
	for (int i = -100; i <= 100; i += 1) //linhas
		for (int j = -100; j <= 100; j += 1) //colunas
		{
			if (count % 2)
				glColor3f(0.5f, 0.5f, 0.5f);
			else glColor3f(1.0f, 1.0f, 1.0f);
			count++;
			glBegin(GL_QUADS);
			glVertex3f(j, -0.5f, i);
			glVertex3f(j, -0.5f, i + 1);
			glVertex3f(j + 1, -0.5f, i + 1);
			glVertex3f(j + 1, -0.5f, i);
			glEnd();
		}
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z, cam.watch.x, cam.watch.y, cam.watch.z, cam.up.x, cam.up.y,cam.up.z);

	cubo.draw();


}

void init(void)
{
	scalex = scaley = scalez = 1.0;
	cubo.readobj("uvmappedcow.obj");
	cubo.setupMesh();
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	
	glLoadIdentity();

}

/*
*  Declare initial window size, position, and display mode
*  (single buffer and RGBA).  Open window with "hello"
*  in its title bar.  Call initialization routines.
*  Register callback function to display graphics.
*  Enter main loop and process events.
*/

void reshape(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(g_window, GLFW_KEY_A)) {
		cam_pos[0] -= cam_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_D)) {
		cam_pos[0] += cam_speed * elapsed_seconds;
		cam_moved = true;
	}

	if (glfwGetKey(g_window, GLFW_KEY_R)) {
		cam_pos[1] += cam_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_F)) {
		cam_pos[1] -= cam_speed * elapsed_seconds;
		cam_moved = true;
	}

	if (glfwGetKey(g_window, GLFW_KEY_W)) {
		cam_pos[2] -= cam_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_S)) {
		cam_pos[2] += cam_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_LEFT)) {
		cam_yaw += cam_yaw_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_RIGHT)) {
		cam_yaw -= cam_yaw_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_UP)) {
		cam_yawvert += cam_yaw_speed * elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_DOWN)) {
		cam_yawvert -= cam_yaw_speed * elapsed_seconds;
		cam_moved = true;
	}

	if (glfwGetKey(g_window, GLFW_KEY_U)) {
		scalex+=0.3*elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_J)) {
		scalex -= 0.3*elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_I)) {
		scaley += 0.3*elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_K)) {
		scaley -= 0.3*elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_O)) {
		scalez += 0.3*elapsed_seconds;
		cam_moved = true;
	}
	if (glfwGetKey(g_window, GLFW_KEY_L)) {
		scalez -= 0.3*elapsed_seconds;
		cam_moved = true;
	}
}

void mouse(int button, int state, int x, int y)
{

}

int main () {


	assert (restart_gl_log ());
/*------------------------------start GL context------------------------------*/
	assert (start_gl ());

/*------------------------------create geometry-------------------------------*/
	init();

/*------------------------------create shaders--------------------------------*/
	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	assert (parse_file_into_str ("test_vs.glsl", vertex_shader, 1024 * 256));
	assert (parse_file_into_str ("test_fs.glsl", fragment_shader, 1024 * 256));
	
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	const GLchar* p = (const GLchar*)vertex_shader;
	glShaderSource (vs, 1, &p, NULL);
	glCompileShader (vs);
	
	// check for compile errors
	int params = -1;
	glGetShaderiv (vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", vs);
		print_shader_info_log (vs);
		return 1; // or exit or something
	}
	
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	p = (const GLchar*)fragment_shader;
	glShaderSource (fs, 1, &p, NULL);
	glCompileShader (fs);
	
	// check for compile errors
	glGetShaderiv (fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", fs);
		print_shader_info_log (fs);
		return 1; // or exit or something
	}
	
	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);
	
	glGetProgramiv (shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (
			stderr,
			"ERROR: could not link shader programme GL index %i\n",
			shader_programme
		);
		print_programme_info_log (shader_programme);
		return false;
	}
	
/*--------------------------create camera matrices----------------------------*/
	/* create PROJECTION MATRIX */
	#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
	// input variables
	float near = 0.1f; // clipping plane
	float far = 100.0f; // clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)g_gl_width / (float)g_gl_height; // aspect ratio
	// matrix components
	float range = tan (fov * 0.5f) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);
	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};
	
	/* create VIEW MATRIX */
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	mat4 view_mat = R * T;

	mat4 model_mat = identity_mat4();
	
	/* get location numbers of matrices in shader programme */
	GLint view_mat_location = glGetUniformLocation (shader_programme, "view");
	GLint proj_mat_location = glGetUniformLocation (shader_programme, "proj");
	int model_mat_location = glGetUniformLocation(shader_programme, "model");

	/* use program (make current in state machine) and set default matrix values*/
	glUseProgram (shader_programme);
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat.m);
	
/*------------------------------rendering loop--------------------------------*/
	/* some rendering defaults */
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_FRONT); // cull back face
	glFrontFace (GL_CW); // GL_CCW for counter clock-wise

	glfwMakeContextCurrent(g_window);
	glfwSwapInterval(1);

	//Setando a callback de teclado
	glfwSetKeyCallback(g_window, keyboard);

	//Setando a callback de reshape
	glfwSetFramebufferSizeCallback(g_window, reshape);

	reshape(g_window, 640, 480);
	
	while (!glfwWindowShouldClose (g_window)) {
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
	    elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
	
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		
		glUseProgram (shader_programme);
		cubo.draw();
		// update other events like input handling 
		
/*-----------------------------move camera here-------------------------------*/
		// control keys
		cam_moved = false;

		glfwPollEvents();

		
		/* update view matrix */
		if (cam_moved) {
			mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
			mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); 
			mat4 RV = rotate_x_deg(identity_mat4(), -cam_yawvert);
			mat4 S = scale(identity_mat4(), vec3(scalex, scaley, scalez));
			mat4 view_mat = RV * R * T * S;
			glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
		}
		
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (g_window);
	}
	
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
