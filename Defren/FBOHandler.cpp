#include "FBOHandler.h"
#include <iostream>


FBOHandler::FBOHandler()
{
}

void FBOHandler::init(GLuint width, GLuint height) {

	GLint maxbuffers;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxbuffers);
	if (NUM_TEXTURES > maxbuffers)
		std::cerr << "ERROR: too many textures specified, GL_MAX_COLOR_ATTACHMENTS: " << maxbuffers << std::endl;

	// generate textures
	glGenTextures(NUM_TEXTURES, textures);

	// CREATE FBO
	glGenFramebuffersEXT(1, &id);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);

	// texture parameteres
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap

	// textures
	for (int i = 0; i < NUM_TEXTURES; i++) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
  		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  		glGenerateMipmapEXT(GL_TEXTURE_2D);
	}

	// attach textures to FBO
	switch (NUM_TEXTURES) {
		case 8: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT7_EXT, GL_TEXTURE_2D, textures[7], 0);
		case 7: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT6_EXT, GL_TEXTURE_2D, textures[6], 0);
		case 6: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT5_EXT, GL_TEXTURE_2D, textures[5], 0);
		case 5: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT4_EXT, GL_TEXTURE_2D, textures[4], 0);
		case 4: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT3_EXT, GL_TEXTURE_2D, textures[3], 0);
		case 3: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_TEXTURE_2D, textures[2], 0);
		case 2: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, textures[1], 0);
		case 1: glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textures[0], 0);
	}

	// check for errors and unbind
	if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
		std::cerr << "ERROR: FBO NOT VALIDATED, ERROR CODE: " << glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) << std::endl;
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}

void FBOHandler::bind(void) {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, id);
}

void FBOHandler::unbind(void) {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void FBOHandler::drawTo(GLuint num) {

	if (num >= NUM_TEXTURES) {
		std::cerr << "WARNING: (FBOHandler) texture outside of range. Tried to bind (write) texture " << num << ", but max is: " << NUM_TEXTURES << std::endl;
		return; 
	}

	switch (num) {
		case 0: glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT); break;
		case 1: glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT); break;
		case 2: glDrawBuffer(GL_COLOR_ATTACHMENT2_EXT); break;
		case 3: glDrawBuffer(GL_COLOR_ATTACHMENT3_EXT); break;
		case 4: glDrawBuffer(GL_COLOR_ATTACHMENT4_EXT); break;
		case 5: glDrawBuffer(GL_COLOR_ATTACHMENT5_EXT); break;
		case 6: glDrawBuffer(GL_COLOR_ATTACHMENT6_EXT); break;
		case 7: glDrawBuffer(GL_COLOR_ATTACHMENT7_EXT); break;
	}
	glClear(GL_COLOR_BUFFER_BIT);
}

void FBOHandler::readFrom(GLuint num) {

	if (num >= NUM_TEXTURES) {
		std::cerr << "WARNING: (FBOHandler) texture outside of range. Tried to bind (read) texture " << num << ", but max is: " << NUM_TEXTURES << std::endl;
		return; 
	}
	glBindTexture(GL_TEXTURE_2D, textures[num]);

	// TODO: this should not be updated all the time?
	glGenerateMipmapEXT(GL_TEXTURE_2D);
}



FBOHandler::~FBOHandler(void)
{

}
