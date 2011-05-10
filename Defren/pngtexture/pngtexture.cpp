#include "pngtexture.h"

GLuint loadPNG(const char* filename)
{
    GLuint textureID;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);

	unsigned error;
	unsigned char* image;
	size_t w, h, x, y;
  
	/*load the PNG in one function call*/

	error = LodePNG_decode32_file(&image, &w, &h, filename);
	/* stop if there is an error*/
	if(error)
	{
		printf("error %u: %s\n", error, LodePNG_error_text(error));
		printf("file: %s \n", filename);
		return 0;
	}
  
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image);
    return textureID;
}