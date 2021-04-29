#include "Renderer.h"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "materials/Material.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;

        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Material& material, const glm::mat4 &view, const glm::mat4 &projection) const
{
    material.GetShader().Bind();
    material.GetShader().SetMVP(material.GetModelMatrix(), view, projection);
    Draw(material.GetVertexArray(), material.GetIndexBuffer(), material.GetShader());
}

void Renderer::Clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
