#pragma once
#include "Material.h"
class Edges : public Material
{
public:
	Edges(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::vector<unsigned int>& indices);
protected:
	void InitializeBufferLayout(VertexBufferLayout& layout) const override;
	void FillData(char* data, int index, int end) const override;
	unsigned int Count() const override;
private:
	struct Line
	{
		glm::vec3 start;
		glm::vec3 end;
		glm::vec3 rightNormal;
		glm::vec3 leftNormal;
	};

	std::vector<Line> lines;

	//std::vector<std::pair<glm::vec3, glm::vec3>> lines;
	//std::vector<glm::vec3> leftNormals;
	//std::vector<glm::vec3> rightNormals;
};

