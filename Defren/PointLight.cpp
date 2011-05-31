#include "PointLight.h"
#include "../libs/include/GL/glew.h"

PointLight::PointLight(float x, float y, float z)
{
	position = glm::vec3(x,y,z);
}


PointLight::~PointLight(void)
{
}

glm::vec3 PointLight::getPosition() {
	float modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
	
	glm::vec3 newPosition;
	
	/*
	glm::mat3 mat;
	for (int col = 0; col < 3; col++)
		for (int row = 0; row < 3; row++)
			mat[col][row] = modelview[col*3+row];

	newPosition = mat._inverse() * position;
	*/
	newPosition.x = position.x * (modelview[0*16+0] + modelview[0*16+1] + modelview[0*16+2]);
	newPosition.y = position.y * (modelview[1*16+0] + modelview[1*16+1] + modelview[1*16+2]);
	newPosition.z = position.z * (modelview[2*16+0] + modelview[2*16+1] + modelview[2*16+2]);
	
	return newPosition;

}


