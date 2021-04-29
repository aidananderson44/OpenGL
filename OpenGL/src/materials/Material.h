#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include "gl/VertexArray.h"
#include "gl/IndexBuffer.h"
#include "gl/VertexBufferLayout.h"
#include "gl/Texture.h"
#include "gl/Shader.h"

class Material
{
public:
	Material(const std::string& path);
	Material(const Material& other);
	Material(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& textureCoordinates, const std::vector<unsigned int>& indices);
	virtual ~Material();

	void Scale(const glm::vec3& scale);
	void Translate(const glm::vec3& translation);
	void Rotate(const float& angle, const glm::vec3& axis);
	const glm::mat4& GetModelMatrix() const;
	const VertexArray& GetVertexArray() const;
	const IndexBuffer& GetIndexBuffer() const;
	const VertexBufferLayout& GetVertexBufferLayout() const;
	const Texture& GetTexture(const std::string &name) const;
	const Shader& GetShader() const;
	void AddTexture(const std::string &name, const Texture&texture);
	void AddTextureFromPath(const std::string& name, const std::string& texturePath);
	void SetShader(const Shader &shader);
	void SetShaderFromPath(const std::string& shaderPath);
	unsigned int Size() const;
	void FillData(char* data) const;
	void ResetModelMatrix();
	
protected:
	virtual void AddToBufferLayout(VertexBufferLayout& layout)const {}
	virtual void FillData(char* data, int index, int end) const;
	std::unique_ptr<std::vector<glm::vec3>> positions;
	std::unique_ptr<std::vector<glm::vec3>> normals;
	std::unique_ptr<std::vector<glm::vec2>> textureCoordinates;
	std::unique_ptr<std::vector<unsigned int>> indices;
private:
	void EnsureGPUObjects() const;
	void EnsureVertexBufferLayout() const;
	mutable std::unique_ptr<VertexArray> vertexArray = nullptr;
	mutable std::unique_ptr<IndexBuffer> indexBuffer = nullptr;
	mutable std::unique_ptr<VertexBuffer> vertexBuffer = nullptr;
	mutable std::unique_ptr<VertexBufferLayout> vertexBufferLayout = nullptr;

	std::unique_ptr<Shader> shader;
	std::vector<std::pair<std::string, Texture>> textures;

	glm::mat4 modelMatrix;

};


