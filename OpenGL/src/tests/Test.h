#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Window.h"
#include "gl/Renderer.h"
namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(const Renderer& renderer) {}
		virtual void OnImGUIRender() {}
		virtual void OnSizeChange(int width, int height);
		virtual void OnKeyChange(Window::Key key, Window::Action action);
		virtual void OnMouseMove(double xDif, double yDif);
		virtual void SetAspectRatio(float aspectRatio) {}
	protected:
		virtual Camera* GetCamera() { return nullptr; }

	};


}