#include "stdafx.h"
#include "CubeManParts.h"


CubeManParts::CubeManParts()
{
}


CubeManParts::~CubeManParts()
{
	Destroy();
}

void CubeManParts::Initialize(D3DXVECTOR3& cubeSize /*= D3DXVECTOR3(1, 1, 1)*/, D3DXVECTOR3& pivot /*= D3DXVECTOR3(0, 0, 0)*/, D3DXVECTOR3& baseLocal /*= D3DXVECTOR3(0, 0, 0)*/)
{
	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(cubeSize.x*(-0.5f) - pivot.x, cubeSize.y*(-0.5f) - pivot.y, cubeSize.z*(-0.5f) - pivot.z);
	vertex[1] = D3DXVECTOR3(cubeSize.x*(-0.5f) - pivot.x, cubeSize.y*(0.5f) - pivot.y, cubeSize.z*(-0.5f) - pivot.z);
	vertex[2] = D3DXVECTOR3(cubeSize.x*(0.5f) - pivot.x, cubeSize.y*(0.5f) - pivot.y, cubeSize.z*(-0.5f) - pivot.z);
	vertex[3] = D3DXVECTOR3(cubeSize.x*(0.5f) - pivot.x, cubeSize.y*(-0.5f) - pivot.y, cubeSize.z*(-0.5f) - pivot.z);
	vertex[4] = D3DXVECTOR3(cubeSize.x*(-0.5f) - pivot.x, cubeSize.y*(-0.5f) - pivot.y, cubeSize.z*(0.5f) - pivot.z);
	vertex[5] = D3DXVECTOR3(cubeSize.x*(-0.5f) - pivot.x, cubeSize.y*(0.5f) - pivot.y, cubeSize.z*(0.5f) - pivot.z);
	vertex[6] = D3DXVECTOR3(cubeSize.x*(0.5f) - pivot.x, cubeSize.y*(0.5f) - pivot.y, cubeSize.z*(0.5f) - pivot.z);
	vertex[7] = D3DXVECTOR3(cubeSize.x*(0.5f) - pivot.x, cubeSize.y*(-0.5f) - pivot.y, cubeSize.z*(0.5f) - pivot.z);

	triangles[0] = TextureTriangle(vertex[7], vertex[6], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[1] = TextureTriangle(vertex[7], vertex[5], vertex[4], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[2] = TextureTriangle(vertex[3], vertex[2], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[3] = TextureTriangle(vertex[3], vertex[6], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[4] = TextureTriangle(vertex[0], vertex[1], vertex[2], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[5] = TextureTriangle(vertex[0], vertex[2], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[6] = TextureTriangle(vertex[4], vertex[5], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[7] = TextureTriangle(vertex[4], vertex[1], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[8] = TextureTriangle(vertex[6], vertex[2], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[9] = TextureTriangle(vertex[6], vertex[1], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[10] = TextureTriangle(vertex[7], vertex[4], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[11] = TextureTriangle(vertex[7], vertex[0], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	D3DXMatrixIdentity(&world);
	rotationAxisX = 0.0f;
	localTranslation = baseLocal;

	child.clear();
}

void CubeManParts::Destroy()
{
	for (auto iter = child.begin(); iter != child.end(); ++iter)
	{
		if (*iter)
		{
			(*iter)->Destroy();
			delete (*iter);
			(*iter) = nullptr;
		}
	}
	child.clear();
}

void CubeManParts::Update(D3DXMATRIX* parentWorldMatrix /*= nullptr*/)
{
	float tick = (float)GameManager::GetTick();

	rotationAxisX += (rotationSpeed * tick);
	if (stopReservation == true 
		&& rotationAxisX < 0.1f 
		&& rotationAxisX > -0.1f)
	{
		stopReservation = false;
		rotationAxisX = 0.0f;
		rotationSpeed = 0.0f;
	}

	float maxAngle = D3DX_PI * 0.25f;
	if (rotationAxisX > maxAngle)
	{
		rotationAxisX = maxAngle;
		rotationSpeed *= -1;
	}
	else if (rotationAxisX < -maxAngle)
	{
		rotationAxisX = -maxAngle;
		rotationSpeed *= -1;
	}

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationX(&rotationMatrix, rotationAxisX);

	D3DXMATRIX localTanslation;
	D3DXMatrixTranslation(&localTanslation, localTranslation.x, localTranslation.y, localTranslation.z);

	world = rotationMatrix * localTanslation;
	if (parentWorldMatrix)
	{
		world *= (*parentWorldMatrix);
	}

	for (auto iter = child.cbegin(); iter != child.cend(); ++iter)
	{
		(*iter)->Update(&world);
	}
}

void CubeManParts::Render()
{
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionTexture::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],
		sizeof(FVF_PositionTexture));

	for (auto iter = child.cbegin(); iter != child.cend(); ++iter)
	{
		(*iter)->Render();
	}
}

void CubeManParts::SetTextureUV(D3DXVECTOR2* uvList)
{
	for (int i = 0; i < TRIANGLE_COUNT; ++i)
	{
		triangles[i].vertex[0].tex = (*(uvList + (i * 3)));
		triangles[i].vertex[1].tex = (*(uvList + (i * 3 + 1)));
		triangles[i].vertex[2].tex = (*(uvList + (i * 3 + 2)));
	}
}