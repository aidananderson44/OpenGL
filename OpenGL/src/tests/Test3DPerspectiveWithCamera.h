#pragma once
#include "Test.h"
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

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void SetAspectRatio(float aspectRatio) override;
		void MouseMove(float dx, float dy) override;
		void MoveForward(float amount) override;
		void Strafe(float amount) override;
		void Fly(float amount) override;
		
	private:
		float aspectRatio = 4.0f / 3.0f;
		float scale = 1.0f;
		int width = 100, height = 100;
		glm::mat4 proj;
		Checkerboad checkerboard;
		Material bunny, teapot;
		Camera camera;
	};
}