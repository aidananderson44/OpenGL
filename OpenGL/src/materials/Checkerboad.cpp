#include "Checkerboad.h"

Checkerboad::Checkerboad(int width, int height)
	:Material(std::vector<glm::vec3>(), std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<unsigned int>()),
	width(width),
	height(height)
{
	int indexCount = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			positions->emplace_back(i, 0, -j);
			positions->emplace_back(i + 1, 0, -j);
			positions->emplace_back(i, 0, -(j + 1));
			positions->emplace_back(i + 1, 0, -(j+1));

			normals->emplace_back(0, 1, 0);
			normals->emplace_back(0, 1, 0);
			normals->emplace_back(0, 1, 0);
			normals->emplace_back(0, 1, 0);

			textureCoordinates->emplace_back(0, 0);
			textureCoordinates->emplace_back(1, 0);
			textureCoordinates->emplace_back(0, 1);
			textureCoordinates->emplace_back(1, 1);

			indices->push_back(indexCount);
			indices->push_back(indexCount + 1);
			indices->push_back(indexCount + 2);
			indices->push_back(indexCount + 2);
			indices->push_back(indexCount + 3);
			indices->push_back(indexCount + 1);

			indexCount += 4;
		}
	}
	SetShaderFromPath("res/shaders/checkerboard.shader");
}

Checkerboad::Checkerboad(const Checkerboad& other)
	:Material(*other.positions, *other.normals, *other.textureCoordinates, *other.indices),
	width(other.width),
	height(other.height)
{
}

void Checkerboad::AddToBufferLayout(VertexBufferLayout& layout) const
{
	layout.Push<float>(1);
}

void Checkerboad::FillData(char* data, int index, int end) const
{
	float result = (((index / 4) + (index / (4 * width))) % 2);
	memcpy(data + end - sizeof(float), &result, sizeof(float));
	Material::FillData(data, index, end - sizeof(float));
}
