#pragma once
#include "FVF.h"

class Grid
{
public:
	Grid();
	~Grid();

	void Initialize(int lineCount = 30, float interval = 1.0f);
	void Destroy();
	void Render();


private:
	std::vector<FVF_PositionColor>	vertices;

	static const int axisCount = 3;

	D3DXMATRIXA16 world;
};

