#pragma once
#include <stack>
#include "../../libs/include/glm/glm.hpp"
#include "../../libs/include/glm/gtc/matrix_transform.hpp"
class TransformationStack
{
public:
	TransformationStack(void);
	~TransformationStack(void);

	void push(glm::mat4 mat);
	void pop();
	void pop(int amount);
	void useTransformation(void);

	void addScale(float scale);
	void addScale(glm::vec3 scale);

	void addTranslation(float x, float y, float z);
	void addTranslation(glm::vec3 vec);

	void addRotation(float angle, float x, float y, float z);
	void addRotation(float angle, glm::vec3 vec);

	static TransformationStack* getStack()
	{
		// Guaranteed to be destroyed, instantiated on first use.
		static TransformationStack instance; 
		return &instance;
	}
	

private:
	std::stack<glm::mat4> *stack;

};

