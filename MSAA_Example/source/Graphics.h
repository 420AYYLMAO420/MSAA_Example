#pragma once
#include <GL/glew.h>
#include <memory>


class Graphics
{
public:

	Graphics();
	~Graphics();

	//draw to the back buffer
	void Render();

	//determines whether MSAA is used or not
	bool isMSAA;
private:

	//vertex shader object
	std::unique_ptr<class VertexShader> VShader;

	//fragment shader object
	std::unique_ptr<class FragmentShader> FShader;

	//id of the OpenGL program
	GLuint idProgram ;

	//id of the vertex buffer
	GLuint idVBuffer;

	//id of the index buffer
	GLuint idIBuffer;

};

