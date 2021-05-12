#include "Quad.h"

Quad::Quad()
	:Material(std::vector<glm::vec3>(), std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<unsigned int>())
{
	positions->emplace_back(-1, -1, 0);
	positions->emplace_back(1, -1, 0);
	positions->emplace_back(-1, 1, 0);
	positions->emplace_back(1, 1, 0);

	normals->emplace_back(0, 0, 1);
	normals->emplace_back(0, 0, 1);
	normals->emplace_back(0, 0, 1);
	normals->emplace_back(0, 0, 1);

	textureCoordinates->emplace_back(0, 0);
	textureCoordinates->emplace_back(1, 0);
	textureCoordinates->emplace_back(0, 1);
	textureCoordinates->emplace_back(1, 1);

	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);
}
