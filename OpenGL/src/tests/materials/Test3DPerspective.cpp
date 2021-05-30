#include "Test3DPerspective.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>

test::Test3DPerspective::Test3DPerspective()
    : rotation(0.0f, 0.0f, 0.0f),
      proj(glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f)),
      view(glm::lookAt(glm::vec3(0, 3, -1), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
    bunny("res/obj/bunny.obj"),
    teapot("res/obj/teapot.obj"),
    checkerboard(width, height)
{
    rotation = glm::vec3(0, 3, -1);
    checkerboard.Translate(glm::vec3(-width / 2, -1.0f, height / 2));

    bunny.SetShaderFromPath("res/shaders/basic3D.shader");
    bunny.Scale(glm::vec3(15, 15, 15));

    teapot.SetShaderFromPath("res/shaders/basic3D.shader");
    teapot.Translate(glm::vec3(10, 0, 0));
}

test::Test3DPerspective::~Test3DPerspective()
{
}

void test::Test3DPerspective::OnUpdate(float deltaTime)
{
}

void test::Test3DPerspective::OnRender(const Renderer& renderer)
{
    renderer.Clear();
    view = glm::lookAt(rotation * scale, glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
    renderer.Draw(checkerboard, view, proj);
    renderer.Draw(bunny, view, proj);
    renderer.Draw(teapot, view, proj);
}

void test::Test3DPerspective::OnImGUIRender()
{
    static float f = 0.0f;
    ImGui::SliderFloat3("Translation", &rotation.x, -3.1415f, 3.1415f, "", 1.0f);
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