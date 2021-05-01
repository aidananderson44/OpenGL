#include "Test.h"
#include"imgui/imgui.h"


test::TestMenu::TestMenu(Test*& currentTestPointer)
	: m_CurrentTest(currentTestPointer)
{

}

test::TestMenu::~TestMenu()
{
}



void test::TestMenu::OnImGUIRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
		{
			m_CurrentTest = test.second();
		}
	}
}

void test::Test::OnUpdate(float deltaTime)
{
	Camera* camera = GetCamera();
	if (camera != nullptr)
		camera->Integrate(deltaTime);
}

void test::Test::OnSizeChange(int width, int height)
{
	Camera* camera = GetCamera();
	if (camera != nullptr)
		camera->SetAspectRatio((float)width / height);
}

void test::Test::OnKeyChange(Window::Key key, Window::Action action)
{
	Camera* camera = GetCamera();
	if (camera != nullptr)
		camera->SetWindowInput(key, action);
}

void test::Test::OnMouseMove(double xDif, double yDif)
{
	Camera* camera = GetCamera();
	if (camera != nullptr)
		camera->Look(xDif, yDif);
}
