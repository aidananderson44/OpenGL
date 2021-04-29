#include "Material.h"
#include "glm/gtc/matrix_transform.hpp"
#include "OBJ_Loader/OBJ_Loader.h"

Material::Material(const std::string& path)
	: modelMatrix(1.0f)
{
	objl::Loader loader = objl::Loader();
	if (loader.LoadFile(path))
	{
		positions = std::make_unique<std::vector<glm::vec3>>();
		positions->reserve(loader.LoadedVertices.size());
		normals = std::make_unique<std::vector<glm::vec3>>();
		normals->reserve(loader.LoadedVertices.size());
		textureCoordinates = std::make_unique<std::vector<glm::vec2>>();
		textureCoordinates->reserve(loader.LoadedVertices.size());
		for (auto& vertex : loader.LoadedVertices)
		{
			positions->emplace_back(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
			normals->emplace_back(vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z);
			textureCoordinates->emplace_back(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y);
		}
		indices = std::make_unique<std::vector<unsigned int>>(loader.LoadedIndices);
	}
	else
	{
		std::cout << "Warning: unable to load Material from path " << path << std::endl;
		positions = std::make_unique<std::vector<glm::vec3>>(0);
		normals = std::make_unique<std::vector<glm::vec3>>(0);
		textureCoordinates = std::make_unique<std::vector<glm::vec2>>(0);
		indices = std::make_unique<std::vector<unsigned int>>(0);
	}
}

Material::Material(const Material& other)
	: modelMatrix(other.modelMatrix)
{
	positions = std::make_unique<std::vector<glm::vec3>>(*other.positions);
	normals = std::make_unique<std::vector<glm::vec3>>(*other.normals);
	textureCoordinates = std::make_unique<std::vector<glm::vec2>>(*other.textureCoordinates);
	indices = std::make_unique<std::vector<unsigned int>>(*other.indices);
}

Material::Material(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& textureCoordinates, const std::vector<unsigned int>& indices)
	:modelMatrix(1.0f)
{
	this->positions = std::make_unique<std::vector<glm::vec3>>(positions);
	this->normals = std::make_unique<std::vector<glm::vec3>>(normals);
	this->textureCoordinates = std::make_unique<std::vector<glm::vec2>>(textureCoordinates);
	this->indices = std::make_unique<std::vector<unsigned int>>(indices);
}

void Material::EnsureGPUObjects() const
{
	if (vertexArray == nullptr)
	{
		EnsureVertexBufferLayout();
		vertexArray = std::make_unique<VertexArray>();
		int stride = vertexBufferLayout->GetStride();
		std::vector<char> data(stride * positions->size());

		for (int i = 0; i < positions->size(); i++)
			FillData(&data[0] + i * stride, i, stride);

		vertexBuffer = std::make_unique<VertexBuffer>(&data[0], stride * positions->size());
		vertexArray->AddBuffer(*vertexBuffer, *vertexBufferLayout);
		indexBuffer = std::make_unique<IndexBuffer>(indices->data(), indices->size());
	}

}

void Material::EnsureVertexBufferLayout() const
{
	if (vertexBufferLayout == nullptr)
	{
		vertexBufferLayout = std::make_unique<VertexBufferLayout>();
		vertexBufferLayout->Push<float>(3);//positions
		vertexBufferLayout->Push<float>(3);//normals
		vertexBufferLayout->Push<float>(2);//texture coordinates
		AddToBufferLayout(*vertexBufferLayout);
	}
}


Material::~Material()
{
}

void Material::Scale(const glm::vec3& scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
}

void Material::Translate(const glm::vec3& translation)
{
	modelMatrix = glm::translate(modelMatrix, translation);
}

void Material::Rotate(const float& angle, const glm::vec3& axis)
{
	modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

const glm::mat4& Material::GetModelMatrix() const
{
	return modelMatrix;
}

const VertexArray& Material::GetVertexArray() const
{
	EnsureGPUObjects();
	return *vertexArray;
}

const IndexBuffer& Material::GetIndexBuffer() const
{
	EnsureGPUObjects();
	return *indexBuffer;
}

const VertexBufferLayout& Material::GetVertexBufferLayout() const
{
	EnsureVertexBufferLayout();
	return *vertexBufferLayout;
}

const Texture& Material::GetTexture(const std::string& name) const
{
	for (auto& pair : textures)
	{
		if (pair.first == name)
			return pair.second;
	}
}

const Shader& Material::GetShader() const
{
	return *shader;
}

void SetTextureUniform(const Shader& shader, const std::vector<std::pair<std::string, Texture>>& textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		shader.Bind();
		textures[i].second.Bind();
		shader.SetUniform1i(textures[i].first, 0);
	}
}

void Material::AddTexture(const std::string& name, const Texture& texture)
{
	textures.emplace_back(name, texture);
	if (shader)
		SetTextureUniform(*this->shader, textures);
}

void Material::AddTextureFromPath(const std::string& name, const std::string& texturePath)
{
	textures.emplace_back(name, texturePath);
	if (shader)
		SetTextureUniform(*this->shader, textures);
}

void Material::SetShader(const Shader& shader)
{
	this->shader = std::make_unique<Shader>(shader);
	SetTextureUniform(*this->shader, textures);
}

void Material::SetShaderFromPath(const std::string& shaderPath)
{
	shader = std::make_unique<Shader>(shaderPath);
	SetTextureUniform(*this->shader, textures);
}

unsigned int Material::Size() const
{
	EnsureVertexBufferLayout();
	return positions->size() * vertexBufferLayout->GetStride();
}

void Material::FillData(char* data) const
{
	EnsureVertexBufferLayout();
	int stride = vertexBufferLayout->GetStride();
	for (int i = 0; i < positions->size(); i++)
		FillData(data + i * stride, i, stride);
}

void Material::ResetModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);
}

void Material::FillData(char* data, int index, int end) const
{
	ASSERT(end == 8 * sizeof(float));
	memcpy(data, (&(*positions)[index]), 3 * sizeof(float));
	memcpy(data + 3 * sizeof(float), (&(*normals)[index]), 3 * sizeof(float));
	memcpy(data + 6 * sizeof(float), (&(*textureCoordinates)[index]), 2 * sizeof(float));
}


