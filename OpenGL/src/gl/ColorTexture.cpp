#include "ColorTexture.h"
#include "stb_image/stb_image.h"
#include "FrameBuffer.h"
#include<memory>
#include "GLMarco.h"
#include <GL/glew.h>
ColorTexture::ColorTexture(const std::string& path)
	: m_RendererID(0), Texture(0, 0)
{
	stbi_set_flip_vertically_on_load(1);
	int bpp;
	std::unique_ptr<char> m_LocalBuffer((char*)stbi_load(path.c_str(), &width, &height, &bpp, 4));

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer.get()));

}

ColorTexture::ColorTexture(int width, int height)
	:m_RendererID(0), Texture(width, height)
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

}

ColorTexture::~ColorTexture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void ColorTexture::Attach(const FrameBuffer& framebuffer) const
{
	Bind();
	framebuffer.Bind();
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RendererID, 0));
}


void ColorTexture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void ColorTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
