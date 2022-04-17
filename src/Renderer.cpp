#include "Renderer.h"

#if defined(__APPLE_CC__)
#include <OpenGL/gl3.h>
#else
#include <GL/gl3.h> /* assert OpenGL 3.2 core profile available. */
#endif
#include <iostream>

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char *file, int line)
{
	bool noError = true;
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << "\n";
		noError = false;
	}
	return noError;
}

void Renderer::clear() const
{
	GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.bind();
	vao.bind();
	ibo.bind();

	GLCALL(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}
