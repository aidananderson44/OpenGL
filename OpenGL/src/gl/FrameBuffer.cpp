#include "FrameBuffer.h"
#include "Texture.h"
#include "GLMarco.h"
#include <GL/glew.h>
#include <iostream>

FrameBuffer::FrameBuffer(int width, int height)
	: texture(width, height), rendererID(0), width(width), height(height)
{
	GLCall(glGenFramebuffers(1, &rendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

	texture.AttachToFrameBuffer(*this);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Warning: Failed to create FrameBuffer";
	UnBind();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &rendererID);
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));	
}

const Texture& FrameBuffer::GetTexture()
{
	return texture;
}

int FrameBuffer::GetWidth()
{
	return width;
}

int FrameBuffer::GetHeight()
{
	return height;
}
