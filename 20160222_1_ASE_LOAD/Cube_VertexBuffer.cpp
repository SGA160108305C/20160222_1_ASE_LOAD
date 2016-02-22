#include "stdafx.h"
#include "Cube_VertexBuffer.h"


Cube_VertexBuffer::Cube_VertexBuffer()
{
}


Cube_VertexBuffer::~Cube_VertexBuffer()
{
}

void Cube_VertexBuffer::Initialize(D3DXVECTOR3& _size, D3DXVECTOR3& _pos)
{
	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-0.5f, 0.0f, -0.5f);
	vertex[1] = D3DXVECTOR3(-0.5f, 1.0f, -0.5f);
	vertex[2] = D3DXVECTOR3(0.5f, 1.0f, -0.5f);
	vertex[3] = D3DXVECTOR3(0.5f, 0.0f, -0.5f);
	vertex[4] = D3DXVECTOR3(-0.5f, 0.0f, 0.5f);
	vertex[5] = D3DXVECTOR3(-0.5f, 1.0f, 0.5f);
	vertex[6] = D3DXVECTOR3(0.5f, 1.0f, 0.5f);
	vertex[7] = D3DXVECTOR3(0.5f, 0.0f, 0.5f);

	FVF_PositionNormal fvfVertex[VERTEX_COUNT];
	fvfVertex[0] = FVF_PositionNormal(vertex[0], D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	fvfVertex[1] = FVF_PositionNormal(vertex[1], D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	fvfVertex[2] = FVF_PositionNormal(vertex[2], D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	fvfVertex[3] = FVF_PositionNormal(vertex[3], D3DXVECTOR3(1.0f, -1.0f, -1.0f));
	fvfVertex[4] = FVF_PositionNormal(vertex[4], D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	fvfVertex[5] = FVF_PositionNormal(vertex[5], D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	fvfVertex[6] = FVF_PositionNormal(vertex[6], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	fvfVertex[7] = FVF_PositionNormal(vertex[7], D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	triangles[0] = NormalTriangle(fvfVertex[0], fvfVertex[1], fvfVertex[2]);
	triangles[1] = NormalTriangle(fvfVertex[0], fvfVertex[2], fvfVertex[3]);
	triangles[2] = NormalTriangle(fvfVertex[4], fvfVertex[5], fvfVertex[1]);
	triangles[3] = NormalTriangle(fvfVertex[4], fvfVertex[1], fvfVertex[0]);
	triangles[4] = NormalTriangle(fvfVertex[7], fvfVertex[6], fvfVertex[5]);
	triangles[5] = NormalTriangle(fvfVertex[7], fvfVertex[5], fvfVertex[4]);
	triangles[6] = NormalTriangle(fvfVertex[3], fvfVertex[2], fvfVertex[6]);
	triangles[7] = NormalTriangle(fvfVertex[3], fvfVertex[6], fvfVertex[7]);
	triangles[8] = NormalTriangle(fvfVertex[1], fvfVertex[5], fvfVertex[6]);
	triangles[9] = NormalTriangle(fvfVertex[1], fvfVertex[6], fvfVertex[2]);
	triangles[10] = NormalTriangle(fvfVertex[4], fvfVertex[0], fvfVertex[3]);
	triangles[11] = NormalTriangle(fvfVertex[4], fvfVertex[3], fvfVertex[7]);

	size = _size;
	position = _pos;

	D3DXMATRIXA16 scale, rotation, translation;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	D3DXMatrixRotationY(&rotation, rotationAngle);
	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);

	world = (scale * rotation * translation);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	material.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	material.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	//버텍스 버퍼
	GameManager::GetDevice()->CreateVertexBuffer(
		sizeof(FVF_PositionNormal) * VERTEX_COUNT,
		0,
		FVF_PositionNormal::FVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		nullptr);
	FVF_PositionNormal* pV;
	vertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy_s(pV, VERTEX_COUNT * sizeof(FVF_PositionNormal),
		fvfVertex, VERTEX_COUNT * sizeof(FVF_PositionNormal));
	vertexBuffer->Unlock();

	//인덱스 버퍼
	GameManager::GetDevice()->CreateIndexBuffer(
		36 * sizeof(DWORD),
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&indexBuffer,
		nullptr
		);

	DWORD index[36];
	index[0] = 0; index[1] = 1; index[2] = 2;
	index[3] = 0; index[4] = 2; index[5] = 3;

	index[6] = 4; index[7] = 5; index[8] = 1;
	index[9] = 4; index[10] = 1; index[11] = 0;

	index[12] = 7; index[13] = 6; index[14] = 5;
	index[15] = 7; index[16] = 5; index[17] = 4;

	index[18] = 3; index[19] = 2; index[20] = 6;
	index[21] = 3; index[22] = 6; index[23] = 7;

	index[24] = 1; index[25] = 5; index[26] = 6;
	index[27] = 1; index[28] = 6; index[29] = 2;

	index[30] = 4; index[31] = 0; index[32] = 3;
	index[33] = 4; index[34] = 3; index[35] = 7;

	LPVOID pI;
	indexBuffer->Lock(0, 0, &pI, 0);
	memcpy_s(pI, 36 * sizeof(DWORD), index, 36 * sizeof(DWORD));
	indexBuffer->Unlock();
}

void Cube_VertexBuffer::Destroy()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
}

void Cube_VertexBuffer::Render()
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

void Cube_VertexBuffer::RenderVB()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	GameManager::GetDevice()->SetMaterial(&material);
	GameManager::GetDevice()->SetTexture(0, nullptr);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionNormal::FVF);

	GameManager::GetDevice()->SetStreamSource(
		0, vertexBuffer, 0, sizeof(FVF_PositionNormal));
	GameManager::GetDevice()->SetIndices(indexBuffer);
	GameManager::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,0,8,0,12
		);
}

void Cube_VertexBuffer::RenderShared()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	GameManager::GetDevice()->SetMaterial(&material);
	GameManager::GetDevice()->SetTexture(0, nullptr);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionNormal::FVF);

	GameManager::GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0, 0, 8, 0, 12
		);
}


void Cube_VertexBuffer::Update()
{

}

void Cube_VertexBuffer::Reset()
{

}
