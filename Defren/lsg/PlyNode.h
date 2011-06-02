#pragma once
#include <vector>
#include "../../libs/include/GL/glew.h"
#include "Node.h"

class PlyNode : public Node
{
public:

	struct Vertex {
		GLfloat x;
		GLfloat y;
		GLfloat z;

		GLfloat nx,ny,nz;
	};

	struct Color {
		GLfloat r;
		GLfloat g;
		GLfloat b;
	};
	
	struct Triangle {
		GLuint v0;
		GLuint v1;
		GLuint v2;
	};

	PlyNode(char *filename);
	~PlyNode(void);
	void render(void);
	void setColor(float r, float g, float b);

private:
	void parse(char *filename);
	Color color;
	Vertex *vertices;
	Triangle *triangles;
	unsigned int vertex_count, face_count;
};

