#pragma once
#include "tests/Test.h"
#include "materials/Checkerboad.h"
#include <memory>
#include "glm/glm.hpp"
#include "Camera.h"

class Material;
namespace test
{
	class Test3DPerspectiveWithCamera : public Test
	{
	public:
		Test3DPerspectiveWithCamera();
		~Test3DPerspectiveWithCamera();

		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;
		Camera* GetCamera() override;
		
	private:
		float scale = 1.0f;
		int width = 100, height = 100;
		Checkerboad checkerboard;
		Material bunny, teapot;
		Camera camera;
	};
}