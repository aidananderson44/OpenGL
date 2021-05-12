#pragma once
#include "ColorTexture.h"
#include "DepthTexture.h"
#include <memory>
class FrameBuffer
{
public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Bind() const;
	static void UnBind();
	
	const std::shared_ptr<ColorTexture>& GetColorTexture() const;
	const std::shared_ptr<DepthTexture>& GetDepthTexture() const;
	int GetWidth();
	int GetHeight();

private:
	int width, height;
	unsigned int rendererID;
	std::shared_ptr<ColorTexture> colorTexture;
	std::shared_ptr<DepthTexture> depthTexture;
};

