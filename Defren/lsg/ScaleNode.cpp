#include "ScaleNode.h"
#include "TransformationStack.h"

ScaleNode::ScaleNode(void)
{
}


ScaleNode::~ScaleNode(void)
{
}

void ScaleNode::setScale(float x, float y, float z) {
	scale = glm::vec3(x,y,z);
}


void ScaleNode::render() {
	TransformationStack *stack = TransformationStack::getStack();
	stack->addScale(scale);
	std::vector<Node *>::iterator it = children->begin();
	while (it != children->end()) {
		(*it)->render();
		++it;
	}
	stack->pop();
}