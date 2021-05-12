#pragma once
#include "Test.h"
#include "materials/Quad.h"
#include "gl/Renderer.h"
#include <memory>
namespace test
{
	class TestSelection : public Test
	{
	public:
		TestSelection();
		template<typename T>
		void RegisterTest(const std::string& name);
		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;
		void OnSizeChange(int width, int height) override;
		void OnKeyChange(Window::Key key, Window::Action action) override;
		void OnMouseMove(double xDif, double yDif) override;
		void SetAspectRatio(float aspectRatio) override;
		

	private:
		int width = 100, height = 100;
		Renderer offScreenRenderer = Renderer::GetOffScreenRenderer(width, height);
		float resolutionScale = 0.5f;
		Quad quad;
		bool renderDepth = false;
		std::unique_ptr<Test> currentTest = nullptr;
		std::vector<std::pair<std::string, std::function<std::unique_ptr<Test>()>>> m_Tests;
		
	};

	template<typename T>
	inline void TestSelection::RegisterTest(const std::string& name)
	{
		std::cout << "Registering test " << name << std::endl;
		m_Tests.push_back(std::make_pair(name, []() { return std::make_unique<T>(); }));
		
	}

}

