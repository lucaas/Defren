#pragma once
#include <GL/glew.h>

static const int NUM_TEXTURES = 4;

class FBOHandler
{
public:
	FBOHandler(void);
	~FBOHandler(void);

	void init(GLuint width = 800, GLuint height = 600);
	void bind(void);
	void unbind(void);
	void drawTo(GLuint num);
	void readFrom(GLuint num);

private:
	GLuint textures[NUM_TEXTURES];
	GLuint id;
};

