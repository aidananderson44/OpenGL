#pragma once
#include "Test.h"
#include "materials/Checkerboad.h"
#include <memory>
#include "glm/glm.hpp"
#include "Camera.h"
#include "LightSource.h"
#include "materials/Quad.h"
class Material;
namespace test
{
	class Test3DShadows : public Test
	{
	public:
		Test3DShadows();
		~Test3DShadows();

		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;
		void OnSizeChange(int width, int height) override;
		Camera* GetCamera() override;
		
	private:
		bool viewFromLight = false;
		float scale = 1.0f;
		int width = 100, height = 100;
		Checkerboad checkerboard;
		Material bunny, teapot;
		Camera camera;
		LightSource lightSource;
		Renderer shadowRenderer = Renderer::GetOffScreenRenderer(width, height);
		Camera* viewPoint = &camera;
		Quad quad;
	};
}