#pragma once

#include "FVF.h"
#include "MaterialTexture.h"


class ObjFileGroup
{
public:
	ObjFileGroup(MaterialTexture* _materialTexture, std::vector<FVF_PositionNormalTexture>& _vertex);
	~ObjFileGroup();

	void Render();

private:
	MaterialTexture* materialTexture = nullptr;
	std::vector<FVF_PositionNormalTexture> vertex;
};

