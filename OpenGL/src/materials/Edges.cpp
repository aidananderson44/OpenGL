#include "Edges.h"

Edges::Edges(const std::vector<glm::vec3>& positions, const std::vector<glm::vec3>& normals, const std::vector<unsigned int> &indices)
	:Material(std::vector<glm::vec3>(), std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<unsigned int>())
{
	for(unsigned int i = 0; i < indices.size() / 3; i++)
	{
		const unsigned int& x = indices[i * 3];
		const unsigned int& y = indices[i * 3 + 1];
		const unsigned int& z = indices[i * 3 + 2];
		glm::vec3 rightNormal = (normals[x] + normals[y] + normals[z]) / 3.0f;
		Line a{ positions[x], positions[y], rightNormal },
			 b{ positions[y], positions[z], rightNormal },
			 c{ positions[z], positions[x], rightNormal };

		const float epsilon = 0.01f;
		for (auto& line : lines)
		{
			if (glm::length(glm::vec2(glm::distance(line.start, a.end), glm::distance(line.start, a.end))) < epsilon)
			{
				line.leftNormal = a.rightNormal;
				a.leftNormal = line.rightNormal;
			}
			else if (glm::length(glm::vec2(glm::distance(line.start, b.end), glm::distance(line.start, b.end))) < epsilon)
			{
				line.leftNormal = b.rightNormal;
				b.leftNormal = line.rightNormal;
			}
			else if (glm::length(glm::vec2(glm::distance(line.start, c.end), glm::distance(line.start, c.end))) < epsilon)
			{
				line.leftNormal = c.rightNormal;
				c.leftNormal = line.rightNormal;
			}
		}
		lines.push_back(a);
		lines.push_back(b);
		lines.push_back(c);
	}
}

void Edges::InitializeBufferLayout(VertexBufferLayout& layout) const
{
	layout.Push<float>(3);//start of line
	layout.Push<float>(3);//end of line
	layout.Push<float>(3);//right hand normal
	layout.Push<float>(3);//Left hand normal
}

void Edges::FillData(char* data, int index, int end) const
{
	memcpy(data, &lines[index], sizeof(Line));
}

unsigned int Edges::Count() const
{
	return lines.size();
}
