#include "DepthTexture.h"
#include "GLMarco.h"
#include <GL/glew.h>
#include "FrameBuffer.h"

DepthTexture::DepthTexture(int width, int height)
	: rendererID(0), Texture(width, height)
{
	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

DepthTexture::~DepthTexture()
{
	GLCall(glDeleteTextures(1, &rendererID));
}

void DepthTexture::Attach(const FrameBuffer& framebuffer) const
{
	Bind();
	framebuffer.Bind();
	GLCall(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rendererID, 0));
}

void DepthTexture::Bind(unsigned int slot) const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void DepthTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
