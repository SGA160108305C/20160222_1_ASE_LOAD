#include "stdafx.h"
#include "Cube_Material.h"


Cube_Material::Cube_Material()
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));	
}

Cube_Material::~Cube_Material()
{
}

void Cube_Material::Initialize(D3DXVECTOR3& _size, D3DXVECTOR3& _pos)
{
	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	vertex[1] = D3DXVECTOR3(-1.0f, 2.0f, -1.0f);
	vertex[2] = D3DXVECTOR3(1.0f, 2.0f, -1.0f);
	vertex[3] = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	vertex[4] = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
	vertex[5] = D3DXVECTOR3(-1.0f, 2.0f, 1.0f);
	vertex[6] = D3DXVECTOR3(1.0f, 2.0f, 1.0f);
	vertex[7] = D3DXVECTOR3(1.0f, 0.0f, 1.0f);

	triangles[0] = NormalTriangle(vertex[0], vertex[1], vertex[2], D3DXVECTOR3(0, 0, -1));
	triangles[1] = NormalTriangle(vertex[0], vertex[2], vertex[3], D3DXVECTOR3(0, 0, -1));
	triangles[2] = NormalTriangle(vertex[4], vertex[5], vertex[1], D3DXVECTOR3(-1, 0, 0));
	triangles[3] = NormalTriangle(vertex[4], vertex[1], vertex[0], D3DXVECTOR3(-1, 0, 0));
	triangles[4] = NormalTriangle(vertex[7], vertex[6], vertex[5], D3DXVECTOR3(0, 0, 1));
	triangles[5] = NormalTriangle(vertex[7], vertex[5], vertex[4], D3DXVECTOR3(0, 0, 1));
	triangles[6] = NormalTriangle(vertex[3], vertex[2], vertex[6], D3DXVECTOR3(1, 0, 0));
	triangles[7] = NormalTriangle(vertex[3], vertex[6], vertex[7], D3DXVECTOR3(1, 0, 0));
	triangles[8] = NormalTriangle(vertex[1], vertex[5], vertex[6], D3DXVECTOR3(0, 1, 0));
	triangles[9] = NormalTriangle(vertex[1], vertex[6], vertex[2], D3DXVECTOR3(0, 1, 0));
	triangles[10] = NormalTriangle(vertex[4], vertex[0], vertex[3], D3DXVECTOR3(0, -1, 0));
	triangles[11] = NormalTriangle(vertex[4], vertex[3], vertex[7], D3DXVECTOR3(0, -1, 0));

	size = _size;
	position = _pos;

	D3DXMATRIXA16 scale, rotation, translation;

	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	D3DXMatrixRotationY(&rotation, rotationAngle);
	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);

	world = (scale * rotation * translation);

	material.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	material.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	material.Specular = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
}

void Cube_Material::Destroy()
{
}

void Cube_Material::Render()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	GameManager::GetDevice()->SetMaterial(&material);
	GameManager::GetDevice()->SetTexture(0, nullptr);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionNormal::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],
		sizeof(FVF_PositionNormal));
}

void Cube_Material::Update()
{
}

void Cube_Material::Reset()
{
}
