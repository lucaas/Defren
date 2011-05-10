#pragma once
#include "../libs/include/GL/glew.h"
#include <vector>

static const int NUM_TEXTURES = 4;

class FBOHandler
{
public:
	FBOHandler(void);
	~FBOHandler(void);

	void init(GLuint width = 1024, GLuint height = 1024);
	void bind(void);
	void unbind(void);
	void drawTo(GLuint num);
	void FBOHandler::drawTo(std::vector<GLuint> v);
	void readFrom(GLuint num);

private:
	GLuint textures[NUM_TEXTURES];
	GLuint id;

	GLenum FBOHandler::getIdFromNum(GLuint num);
};

