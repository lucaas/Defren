#include "Camera.h"

#include <iostream>

#include "../../libs/include/GL/glew.h"
#include "../../libs/include/glm/gtc/matrix_transform.hpp"

Camera::Camera(void)
{
	position = glm::vec3(0.0f, 5.0f, 10.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	matrix = glm::mat4();
}

void Camera::applyTransform() {
	/*
	glRotatef(-rotation.z, 0, 0, 1); // roll
	glRotatef(-rotation.y, 0, 1, 0); // heading
	glRotatef(-rotation.x, 1, 0, 0); // pitch
	glTranslatef(-rotation.x, -rotation.y, -rotation.z); // translate
	*/
	//std::cerr << "using camera: (" << position.x << ", " << position.y << ", " << position.z << ")\t color: (" << center.r << ", " << center.g << ", " << center.b << ")\t up: (" << up.r << ", " << up.g << ", " << up.b << ")" << std::endl;
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(53.0f, 1.f, 1.0f, 50.f);
		gluLookAt(position.x, position.y, position.z, position.x, position.y-5.0f, position.z-10.0f, up.x, up.y, up.z);
		matrix = glm::lookAt(position, position-glm::vec3(0.0f,1.0f,5.0f), up);

	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	//std::cerr << "mat[0]: " << matrix[1][1] << std::endl;


}


glm::vec4 Camera::applyTransformTo(glm::vec3 vec) {
	return matrix * glm::vec4(vec, 1.0f);
}

void Camera::move(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}


Camera::~Camera(void)
{
}