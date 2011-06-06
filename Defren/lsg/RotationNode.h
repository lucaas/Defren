#pragma once
#include "Node.h"
#include "../../libs/include/GL/glew.h"
#include "../../libs/include/glm/glm.hpp"

class RotationNode : public Node
{
private:
	glm::vec3 rotation;
public:
	RotationNode(void);
	~RotationNode(void);
	void render(void);
	void setRotation(float x, float y, float z);
	void setRotation(glm::vec3 vec);
};

