#include "Test3DPerspectiveWithCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>

test::Test3DPerspectiveWithCamera::Test3DPerspectiveWithCamera()
      :proj(glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 1000.0f)),
    bunny("res/obj/bunny.obj"),
    teapot("res/obj/teapot.obj"),
    checkerboard(width, height)
{
    checkerboard.Translate(glm::vec3(-width / 2, -1.0f, height / 2));

    bunny.SetShaderFromPath("res/shaders/basic3D.shader");
    bunny.Scale(glm::vec3(15, 15, 15));

    teapot.SetShaderFromPath("res/shaders/basic3D.shader");
    teapot.Translate(glm::vec3(10, 0, 0));
}

test::Test3DPerspectiveWithCamera::~Test3DPerspectiveWithCamera()
{
}

void test::Test3DPerspectiveWithCamera::OnUpdate(float deltaTime)
{
}

void test::Test3DPerspectiveWithCamera::OnRender()
{
    Renderer renderer;
    renderer.Clear();
    glm::mat4 view = camera.GetViewMatrix();
    renderer.Draw(checkerboard, view, proj);
    renderer.Draw(bunny, view, proj);
    renderer.Draw(teapot, view, proj);
}

void test::Test3DPerspectiveWithCamera::OnImGUIRender()
{
    static float f = 0.0f;
    glm::vec3 position(0, 0, 0);
    ImGui::SliderFloat3("Translation", &position.x, -3.1415, 3.1415, "", 1.0f);
    ImGui::SliderFloat("Scale", &scale, 0, 5, "", 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    camera.MoveTo(position);
}

void test::Test3DPerspectiveWithCamera::SetAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
    if(aspectRatio >= 1)
        proj = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 50.0f);
    else
        proj = glm::perspective(glm::radians(90.0f), 1.0f / aspectRatio, 0.1f, 50.0f);
}

void test::Test3DPerspectiveWithCamera::MouseMove(float dx, float dy)
{
    camera.Look(dx, dy);
}

void test::Test3DPerspectiveWithCamera::MoveForward(float amount)
{
    camera.MoveForward(amount);
}

void test::Test3DPerspectiveWithCamera::Strafe(float amount)
{
    camera.Strafe(amount);
}

void test::Test3DPerspectiveWithCamera::Fly(float amount)
{
    camera.Fly(amount);
}
