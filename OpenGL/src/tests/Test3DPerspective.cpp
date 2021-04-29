#include "Test3DPerspective.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>

test::Test3DPerspective::Test3DPerspective()
    : rotation(0.0f, 0.0f, 0.0f),
      proj(glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 50.0f)),
      view(glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))
{
    rotation = glm::vec3(0, 0, -1);
    checkerboard = std::make_unique<Checkerboad>(100, 100);
    checkerboard->SetShaderFromPath("res/shaders/checkerboard.shader");
    checkerboard->Scale(glm::vec3(0.25f, 0.25f, 0.25f));
    checkerboard->Translate(glm::vec3(-50.0f, -1.0f, 50.0f));
    material = std::make_unique<Material>("res/obj/bunny.obj");
    material->SetShaderFromPath("res/shaders/basic3D.shader");
    material->Scale(glm::vec3(5, 5, 5));
}

test::Test3DPerspective::~Test3DPerspective()
{
}

void test::Test3DPerspective::OnUpdate(float deltaTime)
{
}

void test::Test3DPerspective::OnRender()
{
    Renderer renderer;
    renderer.Clear();
    view = glm::lookAt(rotation * scale, glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
    renderer.Draw(*checkerboard, view, proj);
    renderer.Draw(*material, view, proj);
}

void test::Test3DPerspective::OnImGUIRender()
{
    static float f = 0.0f;
    ImGui::SliderFloat3("Translation", &rotation.x, -3.1415, 3.1415, "", 1.0f);
    ImGui::SliderFloat("Scale", &scale, 0, 5, "", 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void test::Test3DPerspective::SetAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    if(aspectRatio >= 1)
        proj = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 50.0f);
    else
        proj = glm::perspective(glm::radians(90.0f), 1.0f / aspectRatio, 0.1f, 50.0f);
}