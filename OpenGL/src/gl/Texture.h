#pragma once
#include <string>
class FrameBuffer;
class Texture
{
protected:
	int width, height;
public:
	Texture(int width, int height);
	virtual ~Texture();

	virtual void Attach(const FrameBuffer& framebuffer) const = 0;

	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void UnBind() const = 0;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

