#pragma once
#include "Material.h"
class Checkerboad : public Material
{
public:
	Checkerboad(int width, int height);
	Checkerboad(const Checkerboad& other);
protected:
	void AddToBufferLayout(VertexBufferLayout& layout) const override;
	void FillData(char* data, int index, int end) const override;
private:
	int width, height;
};

