#ifndef __PNGTEXTURE_H__
#define __PNGTEXTURE_H__

#include "../../libs/include/GL/glew.h"
#include "lodepng.h"

// Loads a PNG texture and saves it as a mip-map etc..
GLuint loadPNG(const char* filename);


#endif