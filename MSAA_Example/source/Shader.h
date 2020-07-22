#pragma once

#include "Resource.h"

//parent class of all shaders
class Shader : public Resource {
public:
	Shader() {}
	virtual void Make() override {}
	virtual void SetToPipeline() override {}

protected:
	//id of the shader
	unsigned int idShader = 0;

	//id of the program that will use the shader
	unsigned int idProgram = 0;

	//path of the shader file
	const char* FilePath = nullptr;

};