#include "ShaderHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>


ShaderHandler::~ShaderHandler(void)
{
}


bool ShaderHandler::readShaderFile(const char* filename, std::string& out) {
	std::ifstream file;

	file.open(filename);
	if (!file) {
		std::cerr << "ERROR: Can't read shader file: " << filename << std::endl;
		return false;    
	}

	std::stringstream stream;
	stream << file.rdbuf();

	file.close();

	out = stream.str();
	return true;
}

GLint ShaderHandler::createShader(char* file, GLuint type) {
	if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
		std::cerr << "ERROR: Shader, not a valid shader type: " << type << std::endl;
		return 0;
	}

	GLint shader = glCreateShader(type);

	std::string fileContents;
	readShaderFile(file, fileContents);
	const char* assembly = fileContents.c_str();

	glShaderSource(shader, 1, &assembly, NULL);
	glCompileShader(shader);
  
	GLint isCompiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		char str[256];
		glGetShaderInfoLog(shader, 256, NULL, str);
		std::cerr << "ERROR: Shader failed to compile, glGetShaderInfoLog: " << std::endl;
		std::cerr << str << std::endl;
	}

	return shader;
}

void ShaderHandler::createShaders(char* name, char* vertFile, char* fragFile) {
	
	// CREATER SHADERS
	GLint vertexShader = createShader(vertFile, GL_VERTEX_SHADER);
	GLint fragmentShader = createShader(fragFile, GL_FRAGMENT_SHADER);

	// SHADER PROGRAM
	GLint programObj = glCreateProgram();
	glAttachShader(programObj, vertexShader);
	glAttachShader(programObj, fragmentShader);
  
	glLinkProgram(programObj);

	GLint isLinked;
	glGetProgramiv(programObj, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE){
		char str[256];
		glGetProgramInfoLog(programObj, 256, NULL, str);
		std::cerr << "ERROR: Shader program object linking error: " << std::endl;
		std::cerr << str << std::endl;
	}
	else {
		//programs.insert(std::pair<char *, GLint>(name, programObj));
		programs[name] = programObj;
	}
}

GLint ShaderHandler::getProgram(){
	return activeProgram;
}

GLint ShaderHandler::useProgram(char* name) {
	static bool failed = false;
	if (!failed) {
	std::map<const char*, GLint>::iterator it = programs.find(name);
	if (it == programs.end()) {
		std::cerr << "ERROR: Shader program '" << name << "' does not exist. " << std::endl;
		failed = true;
		return 0;
	}
	glUseProgram(it->second);
	activeProgram = it->second;
	return it->second;
	}
	return 0;
}
