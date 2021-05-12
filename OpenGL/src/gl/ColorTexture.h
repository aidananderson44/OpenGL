#pragma once
#include <string>
#include "Texture.h"
class FrameBuffer;
class ColorTexture : public Texture
{
private:
	unsigned int m_RendererID;
public:
	ColorTexture(const std::string& path);
	ColorTexture(int width, int height);
	~ColorTexture() override;

	void Attach(const FrameBuffer& framebuffer) const override;

	void Bind(unsigned int slot = 0) const override;
	void UnBind() const override;
};
