
// Link libraries for WIN32/VS2010)
#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "GLFW" )
#pragma comment( lib, "opengl32" )
#pragma comment( lib, "glu32" )

#include "../libs/include/GL/glew.h"
#include "../libs/include/GL/glfw.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>


#include "FBOHandler.h"
#include "ShaderHandler.h"
#include "pngtexture/pngtexture.h"

static const int WIDTH = 1024;
static const int HEIGHT = 1024;
GLUquadric* quadric;
FBOHandler fbo;
ShaderHandler shaders;
GLuint textureid;

bool toggleShowBuffers = false;

void renderQuad(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
void switchDrawMode3D(bool threeD);
void printGLErrors(void);

void init() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	fbo.init();
	shaders.createShaders("normals", "Shaders/gen_normals.vert", "Shaders/gen_normals.frag");
	shaders.createShaders("lighting", "Shaders/lighting.vert", "Shaders/lighting.frag");

	// Set Up OpenGL
	gluPerspective(43.6,WIDTH/HEIGHT,0.1,10);
	gluLookAt(0,2,4,0,0,0,0,1,0);
	
	quadric = gluNewQuadric();

	textureid = loadPNG("Scene/texture.png");
}

void drawScene() {
	
	// Texture mapped cube
	glBegin(GL_QUADS);
		/*
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		*/
				
		// Back Face
		glNormal3f(0,0,1); glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glNormal3f(0,0,1); glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glNormal3f(0,0,1); glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glNormal3f(0,0,1); glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Bottom Face
		glNormal3f(0,1,0); glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glNormal3f(0,1,0); glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glNormal3f(0,1,0); glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glNormal3f(0,1,0); glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glNormal3f(-1,0,0); glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glNormal3f(-1,0,0); glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glNormal3f(-1,0,0); glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glNormal3f(-1,0,0); glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glNormal3f(1,0,0); glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glNormal3f(1,0,0); glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glNormal3f(1,0,0); glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glNormal3f(1,0,0); glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		/*
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		*/
	glEnd();
	
	
	// Rotating cylinder
	static float angle = 0;
	angle++;

	glPushMatrix();
		glRotatef(angle, 1, 4, 2);
		glTranslatef(0,0,-0.5f);
		glScalef(0.75f, 0.75f, 0.75f);
		gluCylinder(quadric, 1, 0.5f, 1, 36, 36);
	glPopMatrix();
	
}


// OpenGL rendering goes here...
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	fbo.bind();

	
	// FIRST PASS, RENDER SCENE
	switchDrawMode3D(true);
	glColor3f(1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureid);
	GLint program = shaders.useProgram("normals");
	glUniform1i(glGetUniformLocation(program, "texture"), 0); 
	
	// MRT test	
	std::vector<GLuint> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	fbo.drawTo(v);
	
	drawScene();
	
	shaders.disable();
	
	fbo.unbind();
	
	//gluSphere(quadric, 0.5f, 36,36);
	

	// RENDER QUAD(S)
	switchDrawMode3D(false);
	if (toggleShowBuffers) {
		glColor3f(1,1,1);

		fbo.readFrom(0);
		renderQuad(0, 0.5f*WIDTH, 0, 0.5f*HEIGHT);

		fbo.readFrom(1);
		renderQuad(0, 0.5f*WIDTH, 0.5f*HEIGHT, HEIGHT);
	
		fbo.readFrom(2);
		renderQuad(0.5f*WIDTH, WIDTH, 0, 0.5f*HEIGHT);

		fbo.readFrom(3);
		renderQuad(0.5f*WIDTH, WIDTH, 0.5f*HEIGHT, HEIGHT);
	}
	else {
		
		GLint shaderProgram = shaders.useProgram("lighting");

		glActiveTexture(GL_TEXTURE0);
		fbo.readFrom(0);
		glUniform1i(glGetUniformLocation(shaderProgram, "tex_albedo"), 0);

		glActiveTexture(GL_TEXTURE1);
		fbo.readFrom(1);
		GLint uniformLocation = glGetUniformLocation(shaderProgram, "tex_normal");
		if (uniformLocation == -1) {
			std::cerr << "ERROR: Failed to locate uniform variable" << std::endl;
		}
		glUniform1i(uniformLocation, 1);

		glActiveTexture(GL_TEXTURE2);
		fbo.readFrom(2);
		glUniform1i(glGetUniformLocation(shaderProgram, "tex_depth"), 2);

		//glActiveTexture(GL_TEXTURE3);
		//fbo.readFrom(3);
		//glUniform1i(glGetUniformLocation(shaderProgram, "tex_shininess"), 3);

		renderQuad(0, WIDTH, 0, HEIGHT);
		shaders.disable();

	}
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
	if(!glfwOpenWindow(WIDTH, HEIGHT, 8, 8, 8, 8, 8, 0, GLFW_WINDOW)) {
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

		// Toggle with space
		static int spacePress = false;
		if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
			spacePress = true;

		if (spacePress && glfwGetKey(GLFW_KEY_SPACE) == GLFW_RELEASE) {
			spacePress = false;
			toggleShowBuffers = !toggleShowBuffers;
		}
	}


	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}