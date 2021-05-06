#include "Renderer.h"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "materials/Material.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "GLMarco.h"
#include <GL/glew.h>


Renderer::Renderer(int width, int height)
    :width(width), height(height)
{
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    BindFrameBuffer();
    GLCall(glViewport(0, 0, width, height));
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Material& material, const glm::mat4 &view, const glm::mat4 &projection) const
{
    BindFrameBuffer();
    GLCall(glViewport(0, 0, width, height));
    material.GetShader().Bind();
    material.GetShader().SetMVP(material.GetModelMatrix(), view, projection);
    Draw(material.GetVertexArray(), material.GetIndexBuffer(), material.GetShader());
}

void Renderer::Draw(const Material& material, const Camera& camera) const
{
    BindFrameBuffer();
    material.GetShader().Bind();
    material.GetShader().SetMVP(material.GetModelMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
    material.GetShader().SetCameraPosition(camera.GetPosition());
    Draw(material.GetVertexArray(), material.GetIndexBuffer(), material.GetShader());
}

void Renderer::Draw(const Material& material)
{
    BindFrameBuffer();
    GLCall(glViewport(0, 0, width, height));
    material.GetShader().Bind();
    Draw(material.GetVertexArray(), material.GetIndexBuffer(), material.GetShader());
}

void Renderer::Clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Renderer::GetWidth() const
{
    return width;
}

int Renderer::GetHeight() const
{
    return height;
}

const Texture* Renderer::GetTexture() const
{
    if (frameBuffer == nullptr)
        return nullptr;
    else
        return &(frameBuffer->GetTexture());
}

Renderer Renderer::GetOffScreenRenderer(int width, int height)
{  
    Renderer offScreenRenderer(width, height);
    offScreenRenderer.frameBuffer = std::make_unique<FrameBuffer>(width, height);
    return offScreenRenderer;  
}

void Renderer::BindFrameBuffer() const
{
    if (frameBuffer != nullptr)
        frameBuffer->Bind();
    else
        FrameBuffer::UnBind();
}
