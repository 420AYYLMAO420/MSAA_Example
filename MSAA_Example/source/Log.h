#pragma once

#include <GL/glew.h>
#include <stdio.h>

static void glUserClearPrevError() {
	while (glGetError());
}

static bool glUserLog(const char* func, const char* filepath, unsigned int line) {
	while (GLenum err = glGetError()) {
		printf("%s(%d): OpenGL Error(%d): %s\n", filepath, line, err, func);
		return false;
	}
	return true;
}

#define ASSERT(x) if(!(x)){ printf("%s(%d): Assertion Failed\n", __FILE__, __LINE__); __debugbreak(); }
#define GL_USER_ERROR(x) glUserClearPrevError();\
	x; ASSERT(glUserLog(#x, __FILE__, __LINE__));

#define PRINT_IF_ELSE(cond,passMsg,failMsg)\
	if(cond) printf("%s(%d): %s\n", __FILE__, __LINE__, passMsg);\
	else printf("%s(%d): %s\n", __FILE__, __LINE__, failMsg)
