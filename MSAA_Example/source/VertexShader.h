#pragma once

#include "Shader.h"

class VertexShader : public Shader {
public:
	VertexShader(const char* FilePath, unsigned int& programID);
	~VertexShader();

	void Make() override;
	void SetToPipeline() override;

};