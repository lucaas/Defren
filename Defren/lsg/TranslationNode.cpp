#include "TranslationNode.h"
#include "TransformationStack.h"

TranslationNode::TranslationNode(void)
{
}


TranslationNode::~TranslationNode(void)
{
}

void TranslationNode::setTranslation(float x, float y, float z){
	setTranslation(glm::vec3(x,y,z));
}
void TranslationNode::setTranslation(glm::vec3 vec){
	translation = vec;
}

void TranslationNode::render() {
	TransformationStack *stack = TransformationStack::getStack();
	stack->addTranslation(translation);
	std::vector<Node *>::iterator it = children->begin();
	while (it != children->end()) {
		(*it)->render();
		++it;
	}
	stack->pop();
}