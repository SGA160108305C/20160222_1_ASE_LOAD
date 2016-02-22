#include "stdafx.h"
#include "Cube_Texture.h"


Cube_Texture::Cube_Texture()
{
}


Cube_Texture::~Cube_Texture()
{
}

void Cube_Texture::Initialize()
{
	rotateX = 0.0f;
	rotateY = 0.0f;

	D3DXMatrixIdentity(&world);
	D3DXCreateTextureFromFile(
		GameManager::GetDevice(),
		L"./Data/Texture/Box.jpg",
		&texture);

	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertex[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertex[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertex[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertex[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	triangles[0] = TextureTriangle(
		vertex[0], 
		vertex[1], 
		vertex[2], 
		D3DXVECTOR2(0, 1), 
		D3DXVECTOR2(0, 0), 
		D3DXVECTOR2(1, 0));
	triangles[1] = TextureTriangle(vertex[0], vertex[2], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[2] = TextureTriangle(vertex[4], vertex[5], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[3] = TextureTriangle(vertex[4], vertex[1], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[4] = TextureTriangle(vertex[7], vertex[6], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[5] = TextureTriangle(vertex[7], vertex[5], vertex[4], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[6] = TextureTriangle(vertex[3], vertex[2], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[7] = TextureTriangle(vertex[3], vertex[6], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[8] = TextureTriangle(vertex[1], vertex[5], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[9] = TextureTriangle(vertex[1], vertex[6], vertex[2], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[10] = TextureTriangle(vertex[4], vertex[0], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[11] = TextureTriangle(vertex[4], vertex[3], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));
}

void Cube_Texture::Destroy()
{

	SAFE_RELEASE(texture);
}

void Cube_Texture::Update()
{
	float tick = (float)GameManager::GetTick();

	if ((GetAsyncKeyState('A') & 0x8000) != 0)
	{
		rotateY -= (rotateSpeed * tick);
	}
	else if ((GetAsyncKeyState('D') & 0x8000) != 0)
	{
		rotateY += (rotateSpeed * tick);
	}
	if ((GetAsyncKeyState('W') & 0x8000) != 0)
	{
		position += (direction * moveSpeed * tick);
	}
	else if ((GetAsyncKeyState('S') & 0x8000) != 0)
	{
		position -= (direction * moveSpeed * tick);
	}

	D3DXMATRIX rotX, rotY, move;
	D3DXMatrixRotationX(&rotX, rotateX);
	D3DXMatrixRotationY(&rotY, rotateY);

	world = rotX * rotY;

	D3DXVECTOR3 baseDirection(0, 0, 1);
	D3DXVec3TransformCoord(&direction, &baseDirection, &world);


	D3DXMatrixTranslation(&move, position.x, position.y, position.z);
	world *= move;
}

void Cube_Texture::Render()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	GameManager::GetDevice()->SetTexture(0, texture);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionTexture::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],	//triangles,
		sizeof(FVF_PositionTexture));
}


void Cube_Texture::Reset()
{

}


LRESULT Cube_Texture::InputProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		mouseLDown = true;
		mouseStart.x = GET_X_LPARAM(lParam);
		mouseStart.y = GET_Y_LPARAM(lParam);
		result = WM_LBUTTONDOWN;
	}
	break;
	case WM_LBUTTONUP:
	{
		mouseLDown = false;
		result = WM_LBUTTONUP;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (mouseLDown)
		{
			POINT mouseCurrent;
			mouseCurrent.x = GET_X_LPARAM(lParam);
			mouseCurrent.y = GET_Y_LPARAM(lParam);

			int deltaX = mouseCurrent.x - mouseStart.x;
			int deltaY = mouseCurrent.y - mouseStart.y;

			//Spin(deltaX / 100.f, deltaY / 100.f);
			rotateX -= deltaX / 100.0f;
			rotateY -= deltaY / 100.0f;

			mouseStart = mouseCurrent;
			result = WM_MOUSEMOVE;
		}
	}
	break;
	}
	return result;
}
