#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexBufferLayout::VertexBufferLayout()
	: stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout()
{

}

template<typename T>
void VertexBufferLayout::push(int count)
{
	assert(false);
}

template<>
void VertexBufferLayout::push<float>(int count)
{
	elements.emplace_back(GL_FLOAT, count, GL_FALSE);
	stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::push<unsigned int>(int count)
{
	elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
	stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(int count)
{
	elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
	stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
