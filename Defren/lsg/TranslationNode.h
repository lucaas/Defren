#pragma once
#include "Node.h"
#include "../../libs/include/GL/glew.h"
#include "../../libs/include/glm/glm.hpp"

class TranslationNode :public Node
{
private:
	glm::vec3 translation;
public:
	TranslationNode(void);
	~TranslationNode(void);
	void render(void);
	void setTranslation(float x, float y, float z);
	void setTranslation(glm::vec3 vec);
};

