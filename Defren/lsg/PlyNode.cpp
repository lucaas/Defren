#include "PlyNode.h"
#include <iostream>
#include <fstream>
#include <string>


PlyNode::PlyNode(char* filename)
{
	vertex_count = 0;
	face_count = 0;
	parse(filename);
	setColor(0.9f,0.9f,0.9f);
}


PlyNode::~PlyNode(void)
{
}


void PlyNode::parse(char *filename) {
  std::string line;
  std::ifstream file(filename);
  std::cerr << ">>> Loading PLY object." << std::endl; 
  if (file.is_open()) {


    while (file.good()) {
		file >> line;
		if (line.find("element") != -1) {
			file >> line;
			if (line.find("vertex") != -1) {
				file >> vertex_count;
	  			std::cerr << "Vertex count: " << vertex_count << std::endl;  
				vertices = new Vertex[vertex_count];
			}
			if (line.find("face") != -1) {
				file >> face_count;
	  			std::cerr << "Face count: " << face_count << std::endl; 
				triangles = new Triangle[face_count];
			}
		}

		if (line.find("end_header") != -1) {
			// read vertex_count lines
			for (int i=0; i < vertex_count; i++) {
				Vertex v;
				file >> v.x >> v.y >> v.z;
				file >> v.nx >> v.ny >> v.nz;
				file.ignore(256,'\n');
				vertices[i] = v;
				//std::cerr << "x: " << x << "\t y: " << y << "\t z: " << z << std::endl;
			}

			// read face_count lines
			for (int i=0; i < face_count; i++) {
				Triangle t;
				int poly_type;
				file >> poly_type >> t.v0 >> t.v1 >> t.v2;
				//file.ignore(256,'\n');
				triangles[i] = t;
				//std::cerr << "v0: " << t.v0<< "\t v1: " << t.v1 << "\t v2: " << t.v2 << std::endl;
			}
			break;
		}

	}
    file.close();
	std::cerr << ">>> Finished reading object." << std::endl; 
  }
}

void PlyNode::setColor(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}


void PlyNode::render(void) {
	glColor3fv(&color.r);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), vertices);
	glNormalPointer(GL_FLOAT,sizeof(Vertex), &vertices[0].nx);
	//glColorPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0].nx);
	// draw object
	glDrawElements(GL_TRIANGLES, 3*face_count, GL_UNSIGNED_INT, triangles);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


}


