#include "PointLight.h"
#include "../ShaderHandler.h"
#include "Camera.h"

#include <iostream>

PointLight::PointLight(float x, float y, float z)
{
	PointLight(glm::vec3(x,y,z));
}

PointLight::PointLight(glm::vec3 pos)
{
	position = pos;
	color = glm::vec3(0.0f,0.0f,1.0f);
	intensity = 1.0f;
	radius = 1.0f;
}


void PointLight::setColor(float r, float g, float b) {
	color = glm::vec3(r,g,b);
}

void PointLight::setIntensity(float intensity) {
	this->intensity = intensity;
}

void PointLight::setColor(glm::vec3 vec) {
	color = vec;
}

void PointLight::setPosition(glm::vec3 vec) {
	position = vec;
}

PointLight::~PointLight(void)
{
}

void PointLight::useLight() {
	
	// world position -> eye space

	glm::vec4 newPosition = Camera::getCamera()->applyTransformTo(position);
	//std::cerr << "using light: (" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")\t color: (" << color.r << ", " << color.g << ", " << color.b << ")" <<  std::endl;

	// Retrieve shader program for linking
	ShaderHandler *shaderHandler = ShaderHandler::getHandler();
	GLint shaderProgram = shaderHandler->getProgram();

	// Link position
	GLint uniformLocation = glGetUniformLocation(shaderProgram, "light_pos");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: light_pos" << std::endl;
	}
	glUniform3f(uniformLocation, newPosition.x, newPosition.y, newPosition.z);

	// Link color
	uniformLocation = glGetUniformLocation(shaderProgram, "light_color");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: light_color" << std::endl;
	}
	glUniform3f(uniformLocation, color.r, color.g, color.b);
	/*
	// Link Radius
	uniformLocation = glGetUniformLocation(shaderProgram, "light_radius");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: light_radius" << std::endl;
	}
	glUniform1f(uniformLocation, radius);
	*/
	// Link intensity
	uniformLocation = glGetUniformLocation(shaderProgram, "light_intensity");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: light_intensity" << std::endl;
	}
	glUniform1f(uniformLocation, intensity);
	
}


void PointLight::drawLight() {
	glm::vec4 newPosition = Camera::getCamera()->applyTransformTo(position);
	glEnable(GL_POINT_SMOOTH);
	glPointParameterf(GL_POINT_SIZE_MIN, 5.0f);
	glPointParameterf(GL_POINT_SIZE_MAX, 50.0f);
	float quadratic[] = { 1.0f, 0.01f, 0.0f };
	glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, quadratic );
	// testing, draw point at light source
	glBegin(GL_POINTS);
	glColor3f(color.r, color.g, color.b);
	//glColor3f(1,1,1);
	glVertex3f(newPosition.x, newPosition.y, newPosition.z);
	glEnd();
}

