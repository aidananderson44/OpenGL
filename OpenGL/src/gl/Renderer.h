#pragma once

#include <GL/glew.h>
#include <memory>
#include "glm/glm.hpp"
#include "FrameBuffer.h"

class VertexArray;
class IndexBuffer;
class Shader;
class Material;
class Camera;
class Texture;




void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    Renderer(int width, int height);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const Material& material, const glm::mat4& view, const glm::mat4& projection) const;
    void Draw(const Material& material, const Camera& view) const;
    void Draw(const Material& material);
    void Clear() const;
    void SetSize(int width, int height);
    int GetWidth() const;
    int GetHeight() const;
    const Texture* GetTexture()const;

    static Renderer GetOffScreenRenderer(int width, int height);


private:
    int width, height;
    void BindFrameBuffer() const;
    std::unique_ptr<FrameBuffer> frameBuffer = nullptr;
};

