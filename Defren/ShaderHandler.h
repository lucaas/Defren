#pragma once

#include <GL/glew.h>
#include <map>

class ShaderHandler
{
	public:
		ShaderHandler(void);
		~ShaderHandler(void);
		void createShaders(char* name, char* vertFile, char* fragFile); 
		void useProgram(char* name);

		inline void disable(void) { glUseProgram(0); }

	private:
		bool readShaderFile(const char* filename, std::string& out);
		GLint createShader(char* file, GLuint type);

		std::map<const char*, GLint> programs;
};

