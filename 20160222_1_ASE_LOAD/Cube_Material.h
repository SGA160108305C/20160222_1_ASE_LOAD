#pragma once
#include "GameObject.h"
#include "FVF.h"
#include "Triangle.h"

class Cube_Material :
	public GameObject
{
public:
	Cube_Material();
	virtual ~Cube_Material();

	void Initialize(D3DXVECTOR3& _size, D3DXVECTOR3& _pos);
	void Destroy();
	void Render();
	void Update();

	void Reset();

protected:
	static const int TRIANGLE_COUNT = 12;
	NormalTriangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;
	D3DXVECTOR3 size;
	D3DMATERIAL9 material;
};

