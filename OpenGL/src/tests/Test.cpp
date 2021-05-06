#include "Test.h"
#include"imgui/imgui.h"

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
		camera->Look((float)xDif, (float)yDif);
}
