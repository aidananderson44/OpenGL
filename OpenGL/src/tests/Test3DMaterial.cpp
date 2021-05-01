#include "Test3DMaterial.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>

test::Test3DMaterial::Test3DMaterial()
    : rotation(0.0f, 0.0f, 0.0f),
      proj(glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f)),
      view(1.0f)
{
    material = std::make_unique<Material>("res/obj/bunny.obj");
    material->SetShaderFromPath("res/shaders/basic3D.shader");
}

test::Test3DMaterial::~Test3DMaterial()
{
}

void test::Test3DMaterial::OnUpdate(float deltaTime)
{
}

void test::Test3DMaterial::OnRender()
{
    Renderer renderer;
    renderer.Clear();
    material->ResetModelMatrix();
    material->Translate(glm::vec3(0.0f, -1.0f, 0.0f));
    material->Rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    material->Rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    material->Rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    material->Scale(glm::vec3(scale, scale, scale));
    glm::mat4 viewProjection = proj * view;
    renderer.Draw(*material, glm::mat4(1.0f), viewProjection);
}

void test::Test3DMaterial::OnImGUIRender()
{
    static float f = 0.0f;
    ImGui::SliderFloat3("Translation", &rotation.x, -3.1415, 3.1415, "", 1.0f);
    ImGui::SliderFloat("Scale", &scale, 0, 20, "", 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void test::Test3DMaterial::SetAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    if(aspectRatio >= 1)
        proj = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);
    else
        proj = glm::ortho(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio);
}