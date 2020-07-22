#include "FragmentShader.h"
#include <GL/glew.h>
#include <fstream>
#include "Log.h"

FragmentShader::FragmentShader(const char* FilePath, unsigned int& programID)
{
	this->FilePath = FilePath;
	idProgram = programID;
}

FragmentShader::~FragmentShader()
{
	//clean up shader
	GL_USER_ERROR(glDetachShader(idProgram, idShader));
	GL_USER_ERROR(glDeleteShader(idShader));
}

void FragmentShader::Make()
{
	//use the fragment shader file to create the fragment shader
	GL_USER_ERROR(idShader = glCreateShader(GL_FRAGMENT_SHADER));
	std::ifstream FileStream(FilePath);
	std::string ShaderString = std::string(std::istreambuf_iterator<char>(FileStream), std::istreambuf_iterator<char>());
	PRINT_IF_ELSE(FileStream, "Validated fragment shader file", "Fragment shader file is either corrupted or does not exist");
	const GLchar* ShaderCode = ShaderString.c_str();
	GL_USER_ERROR(glShaderSource(idShader, 1, &ShaderCode, NULL));
	GL_USER_ERROR(glCompileShader(idShader));
	GLint isCompiled;
	GL_USER_ERROR(glGetShaderiv(idShader, GL_COMPILE_STATUS, &isCompiled));
	PRINT_IF_ELSE(isCompiled, "Compiled fragment shader", "Failed to compile fragment shader");

}

void FragmentShader::SetPolygonColor(float r, float g, float b, float a)
{
	//set values in uColor in fragment shader 
	GL_USER_ERROR(GLint VertexColorUniform = glGetUniformLocation(idProgram, "uColor"));
	ASSERT(VertexColorUniform != -1);
	GL_USER_ERROR(glUniform4f(VertexColorUniform, r,g,b,a));
}

void FragmentShader::SetToPipeline()
{
	//attach the fragment shader to the program
	GL_USER_ERROR(glAttachShader(idProgram, idShader));
}
