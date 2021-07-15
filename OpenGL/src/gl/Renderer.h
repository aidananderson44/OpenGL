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
class LightSource;

class Renderer
{
public:
    Renderer(int width, int height);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const Material& material, const glm::mat4& view, const glm::mat4& projection) const;
    void Draw(const Material& material, const Camera& view) const;
    void Draw(const Material& material) const;
    void Draw(const Texture& material) const;
    void Draw(Material& material, const Camera& view, const LightSource& lightSource, const std::shared_ptr<Texture>& shadowMap) const;

    void Clear() const;
    void SetSize(int width, int height);
    int GetWidth() const;
    int GetHeight() const;
    void BindFrameBuffer() const;
    const FrameBuffer* GetFrameBuffer()const;

    static Renderer GetOffScreenRenderer(int width, int height);


private:
    int width, height;
    
  //  std::unique_ptr<Quad> quad = nullptr;
    std::unique_ptr<FrameBuffer> frameBuffer = nullptr;
};

