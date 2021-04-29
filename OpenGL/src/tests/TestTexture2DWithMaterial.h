#pragma once
#include "Test.h"
#include <memory>
#include "glm/glm.hpp"

class Material;
namespace test
{
	class TestTexture2DWithMaterial : public Test
	{
	public:
		TestTexture2DWithMaterial();
		~TestTexture2DWithMaterial();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGUIRender() override;
	private:
		const float aspectRatio = 4.0f / 3.0f;
		glm::vec3 translation;
		glm::mat4 proj, view;
		std::unique_ptr<Material> material;
	};
}