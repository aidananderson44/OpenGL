#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"
class VertexArray;
class IndexBuffer;
class Shader;
class Material;
class Camera;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const Material& material, const glm::mat4& view, const glm::mat4& projection) const;
    void Draw(const Material& material, const Camera& view) const;
    void Clear() const;
};

