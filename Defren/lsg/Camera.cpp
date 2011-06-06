#include "Camera.h"

#include <iostream>

#include "../../libs/include/GL/glew.h"
#include "../../libs/include/glm/gtc/matrix_transform.hpp"
#include "../../libs/include/glm/gtc/type_ptr.hpp"
#include "../ShaderHandler.h"

Camera::Camera(void)
{
	position = glm::vec3(0.0f, 2.0f, 10.0f);
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

	glm::mat4 projection_matrix = glm::perspective(45.0f,800.0f/600.0f,1.0f,50.0f);
	matrix = glm::lookAt(position, center, up);

	//std::cerr << "mat[0]: " << matrix[1][1] << std::endl;

	// Bind the "view_matrix" variable in our C++ program to the "view_matrix" variable in the shader
	GLuint uniformLocation = glGetUniformLocation(ShaderHandler::getHandler()->getProgram(), "view_matrix");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: view_matrix" << std::endl;
	}
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(matrix));

	uniformLocation = glGetUniformLocation(ShaderHandler::getHandler()->getProgram(), "projection_matrix");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: view_matrix" << std::endl;
	}
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(projection_matrix));
	

}


glm::vec4 Camera::applyTransformTo(glm::vec3 vec) {
	glm::vec4 result = matrix * glm::vec4(vec, 1.0f);
	return result;
}

void Camera::move(DIRECTION dir) {
	switch (dir) {
	case FORWARD:
		position += 0.1f * forward;
		break;
	case BACK:
		position -= 0.1f * forward;
		break;
	case RIGHT:
		position += 0.1f * glm::cross(forward, up);
		break;
	case LEFT:
		position -= 0.1f * glm::cross(forward, up);
		break;
	}
}


Camera::~Camera(void)
{
}


glm::vec3 sphericalToCartesian(float theta, float phi) {
	float x = cos(theta) * sin(phi);
	float y = sin(theta);
	float z = cos(theta) * cos(phi);
	return glm::vec3(x,y,z);
}

glm::vec3 rotateArbitraryAxis(glm::vec3 v, glm::vec3 u, float theta) {
    glm::vec3 result;

	glm::normalize(u);

    double scalar = glm::dot(v, u);
    double c = cos(theta);
    double s = sin(theta);
    double a = 1.0f - c;

    result.x = u.x * scalar * a + (v.x * c) + ((-u.z * v.y) + (u.y * v.z)) * s;
    result.y = u.y * scalar * a + (v.y * c) + (( u.z * v.x) - (u.x * v.z)) * s;
    result.z = u.z * scalar * a + (v.z * c) + ((-u.y * v.x) + (u.x * v.y)) * s;

    return result;
}
void Camera::rotate(float x, float y) {
		static const float PI = 3.14159265f;
		static float yaw = 0;
		static float pitch = 0;
		yaw += (x > 0) ? 0.5f*x*x : -0.5f*x*x;
		pitch += (y > 0) ? 0.5f*y*y : -0.5f*y*y;

		right = glm::vec3(cos(yaw),0.0f, sin(yaw));
		forward = glm::cross(glm::vec3(0.0f,1.0f,0.0f), right);
		
		forward = rotateArbitraryAxis(forward, right, pitch);
		up = glm::cross(forward, right);
		center = position + forward;
}

