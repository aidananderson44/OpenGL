#include "TestSelection.h"
#include"imgui/imgui.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestTexture2DWithMaterial.h"
#include "tests/Test3DMaterial.h"
#include "tests/Test3DPerspective.h"
#include "tests/Test3DPerspectiveWithCamera.h"
#include "tests/Test3DShadows.h"

test::TestSelection::TestSelection()
{
	this->RegisterTest<test::TestClearColor>("Clear Color");
	this->RegisterTest<test::TestTexture2D>("2D Texture");
	this->RegisterTest<test::TestTexture2DWithMaterial>("2D texture With Material");
	this->RegisterTest<test::Test3DMaterial>("3D Material");
	this->RegisterTest<test::Test3DPerspective>("3D Perspective");
	this->RegisterTest<test::Test3DPerspectiveWithCamera>("3D Perspective with camera");
	this->RegisterTest<test::Test3DShadows>("3D Perspective with shadows");
	quad.SetShaderFromPath("res/shaders/basicMaterial.shader");
}

void test::TestSelection::OnUpdate(float deltaTime)
{
	if (currentTest != nullptr)
		currentTest->OnUpdate(deltaTime);
	
}

void test::TestSelection::OnRender(const Renderer& renderer)
{
	if (currentTest != nullptr)
	{
		//currentTest->OnRender(renderer);
		
		offScreenRenderer.Clear();
		currentTest->OnRender(offScreenRenderer);

		if (renderDepth)
			quad.AddTexture("Texture", (offScreenRenderer.GetFrameBuffer()->GetDepthTexture()));
		else
			quad.AddTexture("Texture", (offScreenRenderer.GetFrameBuffer()->GetColorTexture()));

		renderer.Draw(quad);
	}
}

void test::TestSelection::OnImGUIRender()
{
	ImGui::Begin("Test");
	if (currentTest != nullptr && ImGui::Button("<-"))
		currentTest = nullptr;
	else if (currentTest == nullptr)
	{
		for (auto& test : m_Tests)
			if (ImGui::Button(test.first.c_str()))
			{
				currentTest = test.second();
				currentTest->OnSizeChange(width, height);
			}
	}
	else
		currentTest->OnImGUIRender();
	if(ImGui::SliderFloat("ResolutionScale", &resolutionScale, 0.01f, 2.0f, "%.3f", 32))
		offScreenRenderer.SetSize(width * resolutionScale, height * resolutionScale);
	ImGui::Checkbox("Use Depth Buffer", &renderDepth);
}

void test::TestSelection::OnSizeChange(int width, int height)
{
	this->width = width;
	this->height = height;
	if (currentTest != nullptr)
		currentTest->OnSizeChange(width, height);
	offScreenRenderer.SetSize(width * resolutionScale, height * resolutionScale);

}

void test::TestSelection::OnKeyChange(Window::Key key, Window::Action action)
{
	if (currentTest != nullptr)
		currentTest->OnKeyChange(key, action);
}

void test::TestSelection::OnMouseMove(double xDif, double yDif)
{
	if (currentTest != nullptr)
		currentTest->OnMouseMove(xDif, yDif);
}

void test::TestSelection::SetAspectRatio(float aspectRatio)
{
	if (currentTest != nullptr)
		currentTest->SetAspectRatio(aspectRatio);
}

