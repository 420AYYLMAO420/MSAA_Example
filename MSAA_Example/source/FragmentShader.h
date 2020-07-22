#pragma once

#include "Shader.h"

class FragmentShader : public Shader{
public:
	FragmentShader(const char* FilePath, unsigned int& programID);
	~FragmentShader();
	
	void Make() override;
	void SetPolygonColor(float r, float g, float b, float a);
	void SetToPipeline() override;
};