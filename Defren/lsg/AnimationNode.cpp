#include "AnimationNode.h"
#include "../../libs/include/GL/glew.h"

AnimationNode::AnimationNode(void)
{
}


AnimationNode::~AnimationNode(void)
{
}

void AnimationNode::render(void) {

	static float angle = 0;
	angle += 0.25f;
	glPushMatrix();	
		glTranslatef(0,3,0);
		//glRotatef(angle, 1, 4, 2);
		//glTranslatef(0,0,0.5f);
		glRotatef(angle,0,1,0);
		//glScalef(0.5f,0.5f,0.5f);

		std::vector<Node *>::iterator it = children->begin();
		while (it != children->end()) {
			(*it)->render();
			++it;
		}


	glPopMatrix();

}
