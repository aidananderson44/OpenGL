#include "FrameBuffer.h"
#include "Texture.h"
#include "DepthTexture.h"
#include "GLMarco.h"
#include <GL/glew.h>
#include <iostream>

FrameBuffer::FrameBuffer(int width, int height)
	: colorTexture(std::make_shared<ColorTexture>(width, height)), 
	depthTexture(std::make_shared<DepthTexture>(width, height)), 
	rendererID(0), width(width), height(height)
{
	GLCall(glGenFramebuffers(1, &rendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));


	colorTexture->Attach(*this);
	depthTexture->Attach(*this);
	//depthTexture.AttachAsDepthBuffer(*this);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Warning: Failed to create FrameBuffer";
	UnBind();
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &rendererID));
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void FrameBuffer::UnBind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));	
}

const std::shared_ptr<ColorTexture>& FrameBuffer::GetColorTexture() const
{
	return colorTexture;
}

const std::shared_ptr<DepthTexture>& FrameBuffer::GetDepthTexture() const
{
	return depthTexture;
}

int FrameBuffer::GetWidth()
{
	return width;
}

int FrameBuffer::GetHeight()
{
	return height;
}
