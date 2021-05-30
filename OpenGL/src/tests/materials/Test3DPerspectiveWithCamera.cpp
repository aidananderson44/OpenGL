#include "Test3DPerspectiveWithCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include<vector>

test::Test3DPerspectiveWithCamera::Test3DPerspectiveWithCamera()
    :bunny("res/obj/bunny.obj"),
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

void test::Test3DPerspectiveWithCamera::OnRender(const Renderer& renderer)
{
    renderer.Clear();
    renderer.Draw(checkerboard, camera);
    renderer.Draw(bunny, camera);
    renderer.Draw(teapot, camera);
}

void test::Test3DPerspectiveWithCamera::OnImGUIRender()
{
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

Camera* test::Test3DPerspectiveWithCamera::GetCamera()
{
    return &camera;
}

