#pragma once
#include "VertexBuffer.h"
// #include "VertexBufferLayout.h"
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int rendererID;
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unBind() const;
	void addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);
};
