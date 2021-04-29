#include "TestTexture2D.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"

#include "imgui/imgui.h"




test::TestTexture2D::TestTexture2D()
    : translation(0.0f, 0.0f, 0.0f), 
    proj(glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f)), 
    view(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)))
{
    float positions[]
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    vao->AddBuffer(*vbo, layout);
    ibo = std::make_unique<IndexBuffer>(indices, 6);
    
    shader = std::make_unique<Shader>("res/shaders/Basic.shader");
    shader->Bind();
    texture = std::make_unique<Texture>("res/textures/opengl.png");
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

    vao->Unbind();
    shader->UnBind();
    vbo->UnBind();
    ibo->UnBind();
}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
    Renderer renderer;
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
    glm::mat4 mvp = proj * view * model;

    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);
    renderer.Draw(*vao, *ibo, *shader);

}

void test::TestTexture2D::OnImGUIRender()
{
    static float f = 0.0f;

    ImGui::SliderFloat3("Translation", &translation.x, -1.0f, 1.0f, "", 1.0f);            
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
