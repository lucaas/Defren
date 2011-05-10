
// Link libraries for WIN32/VS2010)
#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "GLFW" )
#pragma comment( lib, "opengl32" )
#pragma comment( lib, "glu32" )

#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "FBOHandler.h"
#include "ShaderHandler.h"

static const int WIDTH = 512;
static const int HEIGHT = 512;
GLUquadric* quadric;
FBOHandler fbo;
ShaderHandler shaders;

void renderQuad(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
void switchDrawMode3D(bool threeD);
void printGLErrors(void);

void init() {
	fbo.init();
	shaders.createShaders("normals", "Shaders/gen_normals.vert", "Shaders/gen_normals.frag");
	glEnable(GL_TEXTURE_2D);

	// Set Up OpenGL
	gluPerspective(43.6,WIDTH/HEIGHT,0.1,10);
	gluLookAt(0,2,4,0,0,0,0,1,0);
	
	quadric = gluNewQuadric();
}


// OpenGL rendering goes here...
void draw() {
	static float angle = 0;
	angle++;

	glEnable(GL_TEXTURE_2D);


	fbo.bind();

	
	// FIRST PASS, RENDER SCENE
	switchDrawMode3D(true);
	glColor3f(1,1,1);
	shaders.useProgram("normals");
	for (int i=0; i < 4; i++) {
		fbo.drawTo(i);
		glPushMatrix();
			glRotatef(angle, i+1, 4-i, i%2);
			gluCylinder(quadric, 1, 0.5f, 1, 36, 36);
		glPopMatrix();
	}
	shaders.disable();

	fbo.unbind();
	
	gluSphere(quadric, 0.5f, 36,36);
	

	// RENDER QUAD(S)
	switchDrawMode3D(false);

	fbo.readFrom(0);
	glColor3f(0.75f, 0.25f, 0.25f);
	renderQuad(0, 0.25f*WIDTH, 0, 0.25f*HEIGHT);

	fbo.readFrom(1);
	glColor3f(0.25f, 0.75f, 0.25f);
	renderQuad(0, 0.25f*WIDTH, 0.25f*HEIGHT, 0.5f*HEIGHT);
	
	fbo.readFrom(2);
	glColor3f(0.25f, 0.25f, 0.75f);
	renderQuad(0, 0.25f*WIDTH, 0.5f*HEIGHT, 0.75f*HEIGHT);

	fbo.readFrom(3);
	glColor3f(0.75f, 0.25f, 0.75f);
	renderQuad(0, 0.25f*WIDTH, 0.75f*HEIGHT, HEIGHT);
	
	glBindTexture(GL_TEXTURE_2D, 0);	

}


void switchDrawMode3D(bool threeD) {
	if (threeD) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(43.6,WIDTH/HEIGHT,0.1,10);
		gluLookAt(0,2,4,0,0,0,0,1,0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WIDTH, 0, HEIGHT);
			
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
void renderQuad(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(left,  top); // Upper Left
		glTexCoord2f(1.0f, 1.0f); glVertex2f(right,  top); // Upper Right
		glTexCoord2f(1.0f, 0.0f); glVertex2f(right, bottom); // Lower Right
		glTexCoord2f(0.0f, 0.0f); glVertex2f(left, bottom); // Lower Left
	glEnd();

}

void printGLErrors(void) {
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cerr << "ERROR: OpenGL returned (" << errCode << "): " << gluErrorString(errCode) << std::endl;

	if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
		std::cerr << "ERROR: FBO NOT VALIDATED, ERROR CODE: " << glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) << std::endl;
}


int main( void )
{
	int running = GL_TRUE;

	// Initialize GLFW
	if(!glfwInit())	{
		exit(EXIT_FAILURE);
	}


	// Open an OpenGL window
	if(!glfwOpenWindow(WIDTH, HEIGHT, 8, 8, 8, 8, 32, 0, GLFW_WINDOW)) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowTitle("Defren");
	glewInit();
	init();

	// Main loop
	while(running) {
		draw();

		// Swap front and back rendering buffers
		glfwSwapBuffers();

		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}


	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}