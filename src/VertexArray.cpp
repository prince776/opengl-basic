#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::bind() const
{
	GLCALL(glBindVertexArray(rendererID));
}

void VertexArray::unBind() const
{
	GLCALL(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	bind();
	vbo.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}
