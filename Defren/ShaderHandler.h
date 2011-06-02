#pragma once

#include "../libs/include/GL/glew.h"
#include <map>

class ShaderHandler
{
	public:
		~ShaderHandler(void);
		void createShaders(char* name, char* vertFile, char* fragFile); 
		GLint useProgram(char* name);
		GLint getProgram();
		inline void disable(void) { glUseProgram(0); activeProgram = 0; }

        static ShaderHandler* getHandler()
        {
			// Guaranteed to be destroyed, instantiated on first use.
            static ShaderHandler instance; 
            return &instance;
        }


	private:
		static ShaderHandler* instance;
		GLint activeProgram;
		bool readShaderFile(const char* filename, std::string& out);
		GLint createShader(char* file, GLuint type);

		std::map<const char*, GLint> programs;

		// Disable asign and copy constructors.
		ShaderHandler() {}
        ShaderHandler(ShaderHandler const&);
        void operator=(ShaderHandler const&);


};

