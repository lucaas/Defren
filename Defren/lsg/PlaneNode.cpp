#include "PlaneNode.h"
#include "TransformationStack.h"
#include "../../libs/include/GL/glew.h"

PlaneNode::PlaneNode(void)
{
}


PlaneNode::~PlaneNode(void)
{
}

void PlaneNode::render(void) {

	TransformationStack *stack = TransformationStack::getStack();
	stack->addScale(10.0f);

	// Bottom Face
	glBegin(GL_QUADS);
	glNormal3f(0,1,0); glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, .0f, -1.0f);	// Top Right Of The Texture and Quad
	glNormal3f(0,1,0); glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, .0f, -1.0f);	// Top Left Of The Texture and Quad
	glNormal3f(0,1,0); glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, .0f,  1.0f);	// Bottom Left Of The Texture and Quad
	glNormal3f(0,1,0); glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, .0f,  1.0f);	// Bottom Right Of The Texture and Quad
	glEnd();

	stack->pop();
}