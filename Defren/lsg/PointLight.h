#pragma once
#include "../../libs/include/glm/glm.hpp"
#include "../../libs/include/GL/glew.h"

class PointLight
{
private:
	glm::vec3 position;
	glm::vec3 color;
	GLfloat radius;
	GLfloat intensity;

public:
	PointLight(float x, float y, float z);
	PointLight(glm::vec3 pos);
	void setColor(float r, float g, float b);
	void setColor(glm::vec3 vec);
	void setPosition(glm::vec3 vec);
	void setIntensity(float intensity);
	~PointLight(void);
	void useLight();
	void drawLight();
};

