#pragma once

#if defined(__APPLE_CC__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/gl3.h> /* assert OpenGL 3.2 core profile available. */
#endif

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define BREAKPOINT asm("int $3")
#define ASSERT(x) if (!(x)) BREAKPOINT

#define GLCALL(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();

bool glLogCall(const char* function, const char *file, int line);

class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& vao, const IndexBuffer &ibo, const Shader& shader) const;
};
