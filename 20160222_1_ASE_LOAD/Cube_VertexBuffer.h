#pragma once
#include "GameObject.h"
#include "Triangle.h"
class Cube_VertexBuffer :
	public GameObject
{
public:
	Cube_VertexBuffer();
	virtual ~Cube_VertexBuffer();

	void Initialize(D3DXVECTOR3& _size, D3DXVECTOR3& _pos);
	void Destroy();
	void Render();
	void RenderVB();
	void RenderShared();
	void Update();

	void Reset();

protected:
	static const int TRIANGLE_COUNT = 12;
	NormalTriangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;
	D3DXVECTOR3 size;
	D3DMATERIAL9 material;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 indexBuffer = nullptr;
};

