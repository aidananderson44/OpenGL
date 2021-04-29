#include "Texture.h"
#include "stb_image/stb_image.h"
#include<memory>
Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	std::unique_ptr<char> m_LocalBuffer((char *)stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4));

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer.get()));
	GLCall(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Texture& other)
	:m_RendererID(other.m_RendererID),
	m_FilePath(other.m_FilePath),
	m_Width(other.m_Width),
	m_Height(other.m_Height),
	m_BPP(other.m_BPP)
{
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind() const
{
	GLCall(GL_TEXTURE_2D, 0);
}
