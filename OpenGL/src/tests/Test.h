#pragma once
#include <vector>
#include <string>
#include<functional>
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Window.h"
namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime);
		virtual void OnRender() {}
		virtual void OnImGUIRender() {}
		virtual void OnSizeChange(int width, int height);
		virtual void OnKeyChange(Window::Key key, Window::Action action);
		virtual void OnMouseMove(double xDif, double yDif);

		virtual void SetAspectRatio(float aspectRatio) {}
	protected:
		virtual Camera* GetCamera() { return nullptr; }

	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();
		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
		void OnImGUIRender() override;

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}