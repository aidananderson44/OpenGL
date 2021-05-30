#pragma once
#include "tests/Test.h"
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

		void OnUpdate(float dt) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;
		void OnSizeChange(int width, int height) override;
		Camera* GetCamera() override;
		
	private:
		float totalTime = 0;
		bool viewFromLight = false;
		float scale = 1.0f;
		float shadowMapScale = 2.0f;
		int width = 100, height = 100;
		Checkerboad checkerboard;
		Material bunny, teapot, armadillo;
		Camera camera;
		LightSource lightSource;
		Renderer shadowRenderer = Renderer::GetOffScreenRenderer(width, height);
		Camera* viewPoint = &camera;
		Quad quad;
	};
}