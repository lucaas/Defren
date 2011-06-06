#include "TransformationStack.h"
#include <iostream>

#include "../../libs/include/GL/glew.h"
#include "../../libs/include/glm/gtc/matrix_transform.hpp"
#include "../../libs/include/glm/gtc/type_ptr.hpp"
#include "../ShaderHandler.h"

TransformationStack::TransformationStack(void)
{
	stack = new std::stack<glm::mat4>;
}


TransformationStack::~TransformationStack(void)
{
}

void TransformationStack::push(glm::mat4 mat) {
	if (stack->empty())
		stack->push(mat);
	else {
		glm::mat4 current = stack->top();
		stack->push(mat * current);
	}
	useTransformation();
}

void TransformationStack::pop(void) {
	if (stack->empty())
		return;
	stack->pop();
	useTransformation();
}

void TransformationStack::pop(int amount) {
	while (amount-- > 0 && !stack->empty())
		stack->pop();
	useTransformation();
}

void TransformationStack::addScale(float scale) {
	addScale(glm::vec3(scale));
}

void TransformationStack::addScale(glm::vec3 scale) {
	glm::mat4 result;
	result = glm::scale(result, scale);
	push(result);
}

void TransformationStack::addTranslation(float x, float y, float z) {
	addTranslation(glm::vec3(x,y,z));
}

void TransformationStack::addTranslation(glm::vec3 vec) {
	glm::mat4 result;
	result = glm::translate(result, vec);
	push(result);
}

void TransformationStack::addRotation(float angle, float x, float y, float z) {
	addRotation(angle, glm::vec3(x,y,z));
}
void TransformationStack::addRotation(float angle, glm::vec3 vec) {
	glm::mat4 result;
	result = glm::rotate(result,angle,vec);
	push(result);
}

void TransformationStack::useTransformation(void) {
	glm::mat4 matrix;
	if (!stack->empty())
		matrix = stack->top();

	GLuint uniformLocation = glGetUniformLocation(ShaderHandler::getHandler()->getProgram(), "model_matrix");
	if (uniformLocation == -1) {
		std::cerr << "ERROR: Failed to locate uniform variable: model_matrix" << std::endl;
	}
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(matrix));
}