#include "AnimationNode.h"
#include "../../libs/include/GL/glew.h"
#include "TransformationStack.h"
AnimationNode::AnimationNode(void)
{
}


AnimationNode::~AnimationNode(void)
{
}

void AnimationNode::render(void) {

	static float angle = 0;
	angle += 0.25f;
	TransformationStack::getStack()->addRotation(angle, 0.0f, 1.0f, 0.0f);
	std::vector<Node *>::iterator it = children->begin();
	while (it != children->end()) {
		(*it)->render();
		++it;
	}
	TransformationStack::getStack()->pop();

}
