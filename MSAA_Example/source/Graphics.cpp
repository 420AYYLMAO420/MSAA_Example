#include "Graphics.h"
#include "Log.h"
#include "VertexShader.h"
#include "FragmentShader.h"


//defines the content of a single vertex
static struct VERTEX {
	struct {
		float X, Y;
	} Position;
};

//array of vertices contained in the vertex buffer
static VERTEX Vertices[] =
{
	{-0.8f, -0.5f},
	{ 0.0f,  0.3f},
	{0.8f, -0.5f},
};

//array of indices contained in the index buffer
static GLuint Indices[] = { 0, 1, 2 };

Graphics::Graphics() {

	//create OpenGL program
	GL_USER_ERROR(idProgram = glCreateProgram());
	PRINT_IF_ELSE(idProgram, "Created OpenGL program", "Failed to create OpenGL program");

	//create vertex shader
	VShader = std::make_unique<VertexShader>("shaders/VertexShader.glsl", idProgram);
	VShader->Make();
	VShader->SetToPipeline();

	//create fragment shader
	FShader = std::make_unique<FragmentShader>("shaders/FragmentShader.glsl", idProgram);
	FShader->Make();
	FShader->SetToPipeline();

	//set OpenGL program for use
	GL_USER_ERROR(glLinkProgram(idProgram));
	GL_USER_ERROR(glUseProgram(idProgram));
	glValidateProgram(idProgram);
	GLint isValid;
	glGetProgramiv(idProgram, GL_VALIDATE_STATUS, &isValid);
	PRINT_IF_ELSE(isValid, "Validated OpenGL program", "OpenGL program is not valid");

	//check if Position2D is a valid variable inside the vertex shader file
	GLint VertexPosAttrib = -1;
	VertexPosAttrib = glGetAttribLocation(idProgram, "Position2D");
	ASSERT(VertexPosAttrib != -1);

	//set triangle color to white
	FShader->SetPolygonColor(1.f, 1.f, 1.f, 1.f);

	//create vertex buffer
	GL_USER_ERROR(glGenBuffers(1, &idVBuffer));
	PRINT_IF_ELSE(idVBuffer > 0, "Created vertex buffer", "Failed to create vertex buffer");
	GL_USER_ERROR(glBindBuffer(GL_ARRAY_BUFFER, idVBuffer));
	GL_USER_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW));

	//create index buffer
	GL_USER_ERROR(glGenBuffers(1, &idIBuffer));
	PRINT_IF_ELSE(idVBuffer > 0, "Created index buffer", "Failed to create index buffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	//create position attribute
	GL_USER_ERROR(glVertexAttribPointer(VertexPosAttrib, 
		sizeof(Vertices->Position) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertices->Position), NULL));
	GL_USER_ERROR(glEnableVertexAttribArray(VertexPosAttrib));

	//prepare OpenGL for multisampling
	GL_USER_ERROR(glEnable(GL_BLEND));
	GL_USER_ERROR(glDisable(GL_DEPTH_TEST));
	GL_USER_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_USER_ERROR(glHint(GL_LINE_SMOOTH_HINT, GL_NICEST));
	GL_USER_ERROR(glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST));
	GL_USER_ERROR(glDisable(GL_LINE_SMOOTH));
	GL_USER_ERROR(glDisable(GL_POLYGON_SMOOTH));
	GL_USER_ERROR(glDisable(GL_MULTISAMPLE));

	//use red to clear back buffer
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

Graphics::~Graphics()
{
	//clean up OpenGL
	GL_USER_ERROR(glDeleteBuffers(1, &idVBuffer));
	GL_USER_ERROR(glDeleteBuffers(1, &idVBuffer));
	GL_USER_ERROR(glDeleteProgram(idProgram));
}

void Graphics::Render()
{	
	//clear back buffer
	GL_USER_ERROR(glClear(GL_COLOR_BUFFER_BIT));

	//check if multisampling is enabled
	if (isMSAA) {
		GL_USER_ERROR(glEnable(GL_LINE_SMOOTH));
		GL_USER_ERROR(glEnable(GL_POLYGON_SMOOTH));
		GL_USER_ERROR(glEnable(GL_MULTISAMPLE));
	}
	else {
		GL_USER_ERROR(glDisable(GL_LINE_SMOOTH));
		GL_USER_ERROR(glDisable(GL_POLYGON_SMOOTH));
		GL_USER_ERROR(glDisable(GL_MULTISAMPLE));
	}
		
	//draw the triangle 
	GL_USER_ERROR(glDrawElements(GL_TRIANGLE_FAN, std::size(Indices), GL_UNSIGNED_INT, NULL));
}
