#include "TestTexture2DWithMaterial.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>



test::TestTexture2DWithMaterial::TestTexture2DWithMaterial()
    : translation(0.0f, 0.0f, 0.0f),
      proj(glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f)),
      view(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)))
{
    std::vector<glm::vec3> positions = 
    {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        { 0.5f, 0.5f, 0.0f},
        {-0.5f, 0.5f, 0.0f}
    };

    std::vector<glm::vec3> normals =
    {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    };

    std::vector<glm::vec2> textureCoords =
    {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    material = std::make_unique<Material>(positions, normals, textureCoords, indices);
    material->SetShaderFromPath("res/shaders/basicMaterial.shader");
    material->AddTextureFromPath("u_Texture", "res/textures/opengl.png");
}

test::TestTexture2DWithMaterial::~TestTexture2DWithMaterial()
{
}

void test::TestTexture2DWithMaterial::OnUpdate(float deltaTime)
{
}

void test::TestTexture2DWithMaterial::OnRender(const Renderer& renderer)
{
    renderer.Clear();
    material->ResetModelMatrix();
    material->Translate(translation);
    glm::mat4 viewProjection = proj * view;
    renderer.Draw(*material, glm::mat4(1.0f), viewProjection);
}

void test::TestTexture2DWithMaterial::OnImGUIRender()
{
    static float f = 0.0f;
    ImGui::SliderFloat3("Translation", &translation.x, -1.0f, 1.0f, "", 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
