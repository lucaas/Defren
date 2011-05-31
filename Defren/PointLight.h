#pragma once
#include "../libs/include/glm/glm.hpp"

class PointLight
{
private:
	glm::vec3 position;
	glm::vec3 color;

public:
	PointLight(float x, float y, float z);
	~PointLight(void);
	glm::vec3 getPosition();
};

