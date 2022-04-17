#pragma once

#include "Renderer.h"
#include <string>

class Texture
{
private:
	unsigned int rendererID;
	std::string filepath;
	unsigned char* localBuffer;
	int width, height, BPP;
public:
    Texture(const std::string &path);
    ~Texture();

	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
};
