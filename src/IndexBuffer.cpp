#include "IndexBuffer.h"
#include "Renderer.h"
 
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCALL(glGenBuffers(1, &rendererID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unBind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
