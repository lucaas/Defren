
// Link libraries for WIN32/VS2010)
#pragma comment( lib, "glew32.lib" )
#pragma comment( lib, "GLFW" )
#pragma comment( lib, "opengl32" )
#pragma comment( lib, "glu32" )

#include "../libs/include/GL/glew.h"
#include "../libs/include/GL/glfw.h"
#include "../libs/include/glm/glm.hpp"

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>


#include "FBOHandler.h"
#include "ShaderHandler.h"
#include "pngtexture/pngtexture.h"
#include "lsg/Scene.h"
#include "lsg/Camera.h"


static const int WIDTH = 800;
static const int HEIGHT = 600;
GLUquadric* quadric;
FBOHandler fbo;
ShaderHandler *shaders;
Scene *scene;

GLuint textureid;

GLfloat rot_x = 0, rot_z = 0;
bool mousePressed = false;
bool toggleShowBuffers = true;
int zoom = 0;

void renderQuad(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
void switchDrawMode3D(bool threeD);
void printGLErrors(void);

void init() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);


	fbo.init(WIDTH, HEIGHT);
	shaders = ShaderHandler::getHandler();
	shaders->createShaders("normals", "Shaders/gen_normals.vert", "Shaders/gen_normals.frag");
	shaders->createShaders("lighting", "Shaders/lighting.vert", "Shaders/lighting.frag");

	// Set Up OpenGL
	quadric = gluNewQuadric();

	textureid = loadPNG("Scene/texture.png");
	scene = new Scene();
}
/*
void drawScene() {
	
	// Texture mapped cube
	glPushMatrix();
	glScalef(2,2,2);
	glBegin(GL_QUADS);
		
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		
				
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
		
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		
	glEnd();
	glPopMatrix();
	
	// Rotating cylinder
	
	static float angle = 0;
	angle++;

	glPushMatrix();
		glColor3f(0.75f, 0.5f, 0.5f);
		
		glRotatef(angle, 1, 4, 2);
		glTranslatef(0,0,-0.5f);
		glRotatef(angle,1,0,0);

		//glScalef(5,5,5);
		glScalef(0.5f,0.5f,0.5f);
		node->render();
	glPopMatrix();


	
}

*/
// OpenGL rendering goes here...
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	fbo.bind();

	
	// FIRST PASS, RENDER SCENE
	switchDrawMode3D(true);
	glColor3f(1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureid);
	GLint program = shaders->useProgram("normals");
	glUniform1i(glGetUniformLocation(program, "texture"), 0); 
	
	// MRT test	
	std::vector<GLuint> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	fbo.drawTo(v);



	//glRotatef( rot_x*0.5f, 1.0f, 0.0f, 0.0f );
	//glRotatef( rot_z*0.5f, 0.0f, 0.0f, 1.0f ); 
	scene->render();


	shaders->disable();
	
	fbo.unbind();
	
	//gluSphere(quadric, 0.5f, 36,36);
	

	// RENDER QUAD(S)
	switchDrawMode3D(false);
	if (toggleShowBuffers) {
		glColor3f(1,1,1);

		fbo.readFrom(0);
		renderQuad(0, 0.25f*WIDTH, 0, 0.25f*HEIGHT);

		fbo.readFrom(1);
		renderQuad(0.25f*WIDTH, 0.5f*WIDTH, 0, 0.25f*HEIGHT);
	
		fbo.readFrom(2);
		renderQuad(0.5f*WIDTH, 0.75f*WIDTH, 0, 0.25f*HEIGHT);

		fbo.readFrom(3);
		renderQuad(0.75f*WIDTH, WIDTH, 0, 0.25f*HEIGHT);
	}
	



	GLint shaderProgram = shaders->useProgram("lighting");

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
	glUniform1i(glGetUniformLocation(shaderProgram, "tex_position"), 2);

	//glActiveTexture(GL_TEXTURE3);
	//fbo.readFrom(3);
	//glUniform1i(glGetUniformLocation(shaderProgram, "tex_shininess"), 3);


	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE, GL_ONE);
	
	std::vector<PointLight>::iterator it = scene->lights.begin();
	std::vector<PointLight>::iterator end = scene->lights.end();
	while (it != end) {
		(*it).useLight();
		renderQuad(0, WIDTH, 0, HEIGHT);
		++it;
	}


	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	shaders->disable();

	
	glBindTexture(GL_TEXTURE_2D, 0);	

	printGLErrors();
}


void switchDrawMode3D(bool threeD) {
	if (threeD) {
		Camera::getCamera()->applyTransform();
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

void mouseMoved(int x, int y) {
	if (true) {
		// std::cerr << "mouse pos: x:" << x << "\t y:" << y << std::endl;
		static int xpos = 0;
		static int ypos = 0;

		rot_x += y - ypos;
		rot_z += x - xpos; 

		xpos = x;
		ypos = y;
	}
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
	glfwSetWindowPos(300,100);
	glfwSetWindowTitle("Defren");
	 
	glfwSetMousePosCallback((GLFWmouseposfun) mouseMoved);
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

		if (glfwGetKey('A') == GLFW_PRESS)
			Camera::getCamera()->move(-0.25f, 0, 0);
		if (glfwGetKey('D') == GLFW_PRESS)
			Camera::getCamera()->move(0.25f, 0, 0);
		if (glfwGetKey('W') == GLFW_PRESS)
			Camera::getCamera()->move(0.0f, 0, -0.25f);
		if (glfwGetKey('S') == GLFW_PRESS)
			Camera::getCamera()->move(0.0f, 0, 0.25f);

		// Mouse press = enable rotate
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
			mousePressed = true;
		else
			mousePressed = false;

		// Mouse scroll, zoom
		zoom = glfwGetMouseWheel();
	}


	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}