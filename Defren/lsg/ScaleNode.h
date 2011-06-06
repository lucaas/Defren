#pragma once
#include "Node.h"
#include "../../libs/include/glm/glm.hpp"

class ScaleNode :
	public Node
{
private:
	glm::vec3 scale;
public:
	ScaleNode(void);
	~ScaleNode(void);
	void render();
	void setScale(float x, float y, float z);
};

