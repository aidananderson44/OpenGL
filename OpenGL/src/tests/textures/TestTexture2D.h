#pragma once
#include "tests/Test.h"
#include "gl/VertexBuffer.h"
#include "gl/VertexBufferLayout.h"
#include "gl/Texture.h"
#include <memory>
#include "glm/glm.hpp"
#include "gl/VertexArray.h"
#include "gl/Shader.h"
#include "gl/IndexBuffer.h"
namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGUIRender() override;
	private:
		const float aspectRatio = 4.0f / 3.0f;
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<IndexBuffer> ibo;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<Texture> texture;
		glm::vec3 translation;
		glm::mat4 proj, view;
	};
}