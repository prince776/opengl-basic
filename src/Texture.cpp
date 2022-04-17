#include "Texture.h"
#include "stb/stb_image.h"

Texture::Texture(const std::string &path)
	: rendererID(0), filepath(path), localBuffer(nullptr), width(0), height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(1); 
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	GLCALL(glGenTextures(1, &rendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, rendererID));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));	

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)localBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &rendererID));
}

void Texture::bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Texture::unBind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
