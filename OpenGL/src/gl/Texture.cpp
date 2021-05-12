#include "Texture.h"
#include "stb_image/stb_image.h"
#include "FrameBuffer.h"
#include<memory>
#include "GLMarco.h"
#include <GL/glew.h>

Texture::Texture(int width, int height)
	:width(width), height(height)
{

}



Texture::~Texture()
{
}

