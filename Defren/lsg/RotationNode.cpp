#include "RotationNode.h"
#include "TransformationStack.h"

RotationNode::RotationNode(void)
{
}


RotationNode::~RotationNode(void)
{
}

void RotationNode::setRotation(float x, float y, float z){
	setRotation(glm::vec3(x,y,z));
}
void RotationNode::setRotation(glm::vec3 vec){
	rotation = vec;
}

void RotationNode::render() {
	TransformationStack *stack = TransformationStack::getStack();
	stack->addRotation(rotation.x, 1,0,0);
	stack->addRotation(rotation.y, 0,1,0);
	stack->addRotation(rotation.z, 0,0,1);

		std::vector<Node *>::iterator it = children->begin();
		while (it != children->end()) {
			(*it)->render();
			++it;
		}
	stack->pop(3);
}