#include "VertexShader.h"
#include <GL/glew.h>
#include <fstream>
#include "Log.h"

VertexShader::VertexShader(const char* FilePath, unsigned int& programID)
{
	this->FilePath = FilePath;
	idProgram = programID;
	
}

VertexShader::~VertexShader()
{
	//clean up shader
	GL_USER_ERROR(glDetachShader(idProgram, idShader));
	GL_USER_ERROR(glDeleteShader(idShader));
}

void VertexShader::Make()
{
	//use the vertex shader file to create the vertex shader
	GL_USER_ERROR(idShader = glCreateShader(GL_VERTEX_SHADER));
	PRINT_IF_ELSE(idShader >= 0, "Created vertex shader", "Failed to create vertex shader");
	std::ifstream FileStream(FilePath);
	PRINT_IF_ELSE(FileStream, "Validated vertex shader file", "Vertex shader file is either corrupted or does not exist");
	std::string ShaderString = std::string(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
	const GLchar* ShaderCode = ShaderString.c_str();
	GL_USER_ERROR(glShaderSource(idShader, 1, &ShaderCode, NULL));
	GL_USER_ERROR(glCompileShader(idShader));
	GLint isCompiled;
	GL_USER_ERROR(glGetShaderiv(idShader, GL_COMPILE_STATUS, &isCompiled));
	PRINT_IF_ELSE(isCompiled, "Compiled vertex shader", "Failed to compile vertex shader");
}

void VertexShader::SetToPipeline()
{
	//attach the vertex shader to the program
	GL_USER_ERROR(glAttachShader(idProgram, idShader));
}
