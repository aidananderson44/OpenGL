#pragma once
#include "Texture.h"
class FrameBuffer;
class DepthTexture : public Texture
{
private:
	unsigned int rendererID;
public:
	DepthTexture(int width, int height);
	~DepthTexture() override;

	void Attach(const FrameBuffer& framebuffer) const override;

	void Bind(unsigned int slot = 0) const override;
	void UnBind() const override;

};
