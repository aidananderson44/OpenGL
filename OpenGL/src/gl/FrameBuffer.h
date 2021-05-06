#pragma once
#include "Texture.h"
class Texture;
class FrameBuffer
{
public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Bind() const;
	static void UnBind();
	
	const Texture& GetTexture();
	int GetWidth();
	int GetHeight();

private:
	int width, height;
	unsigned int rendererID;
	Texture texture;
};

