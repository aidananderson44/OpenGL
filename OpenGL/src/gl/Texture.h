#pragma once
#include <string>
class FrameBuffer;
class Texture
{
private:
	unsigned int m_RendererID;
	int m_Width, m_Height;
public:
	Texture(const std::string& path);
	Texture(int width, int height);
	Texture(const Texture& other);
	~Texture();

	void AttachToFrameBuffer(const FrameBuffer& framebuffer);

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

