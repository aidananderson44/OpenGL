#include "Test3DShadows.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/Renderer.h"
#include "materials/Material.h"
#include "imgui/imgui.h"
#include "gl/GLMarco.h"
#include<vector>

test::Test3DShadows::Test3DShadows()
    :bunny("res/obj/bunny.obj"),
    teapot("res/obj/teapot.obj"),
    armadillo("res/obj/armadillo.obj"),
    checkerboard(width, height)
{
    checkerboard.Translate(glm::vec3(-width / 2, 0.0f, height / 2));

    bunny.SetShaderFromPath("res/shaders/3DLightAndShadows.shader");
   // bunny.SetShaderFromPath("res/shaders/basic3D.shader");
    bunny.Translate(glm::vec3(0.0f, -0.5f, 0.0f));
    bunny.Scale(glm::vec3(15, 15, 15));
    
    armadillo.SetShaderFromPath("res/shaders/3DLightAndShadows.shader");
    teapot.SetShaderFromPath("res/shaders/3DLightAndShadows.shader");
    //teapot.SetShaderFromPath("res/shaders/basic3D.shader");
    teapot.Translate(glm::vec3(10, 0, 0));
    armadillo.Translate(glm::vec3(0, 1, 5));
    lightSource.MoveTo(glm::vec3(-25.0f, 30.0f, 25.0f));
    lightSource.LookAt(glm::vec3(3, 0, 0));
 //   lightSource.GetViewMatrix();
    lightSource.Color = glm::vec3(1.0f, 1.0f, 1.0f);
    quad.SetShaderFromPath("res/shaders/basicMaterial.shader");
    checkerboard.SetShaderFromPath("res/shaders/checkerboardWithShadow.shader");
}

test::Test3DShadows::~Test3DShadows()
{

}



void test::Test3DShadows::OnUpdate(float dt)
{
    totalTime += dt;
    lightSource.MoveTo(glm::vec3(15 * cos(totalTime / 3000.0f), 15 + 5 * sin(totalTime / 1000.0f), 15 * sin(totalTime / 3000.0f)));
    lightSource.LookAt(glm::vec3(0, 0, 0));
    Test::OnUpdate(dt);
}

void test::Test3DShadows::OnRender(const Renderer& renderer)
{
    shadowRenderer.Clear();
    shadowRenderer.Draw(checkerboard, lightSource);
    shadowRenderer.Draw(bunny, lightSource);
    shadowRenderer.Draw(teapot, lightSource);
    shadowRenderer.Draw(armadillo, lightSource);
    std::shared_ptr<Texture> depthTexture = shadowRenderer.GetFrameBuffer()->GetDepthTexture();
    renderer.Draw(checkerboard, *viewPoint, lightSource, depthTexture);
    renderer.Draw(bunny, *viewPoint, lightSource, depthTexture);
    renderer.Draw(teapot, *viewPoint, lightSource, depthTexture);
    renderer.Draw(armadillo, *viewPoint, lightSource, depthTexture);
}

void test::Test3DShadows::OnImGUIRender()
{    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    if (ImGui::Checkbox("View From Light Source", &viewFromLight))
        viewPoint = viewFromLight ? &lightSource : &camera;
}

void test::Test3DShadows::OnSizeChange(int width, int height)
{
    shadowRenderer.SetSize((int)(width * shadowMapScale), (int)(height * shadowMapScale));
    Test::OnSizeChange(width, height);
}

Camera* test::Test3DShadows::GetCamera()
{
    return &camera;
}
