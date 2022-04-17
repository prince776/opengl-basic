#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
		: type(type), count(count), normalized(normalized)
		{}
	
	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned int stride;
	std::vector<VertexBufferElement> elements;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

	template<typename T>
	void push(int count);

	inline unsigned int getStride() const { return stride; }
	inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
};
