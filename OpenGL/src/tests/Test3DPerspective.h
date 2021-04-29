#pragma once
#include "Test.h"
#include "materials/Checkerboad.h"
#include <memory>
#include "glm/glm.hpp"

class Material;
namespace test
{
	class Test3DPerspective : public Test
	{
	public:
		Test3DPerspective();
		~Test3DPerspective();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
		void SetAspectRatio(float aspectRatio) override;
		
	private:
		float aspectRatio = 4.0f / 3.0f;
		float scale = 1.0f;
		int width = 1000, height = 1000;
		glm::vec3 rotation;
		glm::mat4 proj, view;
		Checkerboad checkerboard;
		Material bunny, teapot;
	};
}