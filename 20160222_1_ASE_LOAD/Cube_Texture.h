#pragma once
#include "Triangle.h"

class Cube_Texture
{
public:
	Cube_Texture();
	~Cube_Texture();

	void Initialize();
	void Destroy();
	void Update();
	void Render();
	
	void Reset();

	LRESULT InputProc(
		HWND hWnd, UINT message, 
		WPARAM wParam, LPARAM lParam);

	inline const LPD3DXVECTOR3
		GetPositionAdress(){ return &position; }

private:
	D3DXVECTOR3 position = D3DXVECTOR3(0,0,0);

	float rotateX = 0.0f;
	float rotateY = 0.0f;

	bool mouseLDown = false;
	POINT mouseStart;

	D3DXVECTOR3	direction = D3DXVECTOR3(0, 0, 0);

	float moveSpeed = 10.0f;
	float rotateSpeed = 3.0f;

	LPDIRECT3DTEXTURE9 texture = nullptr;

	D3DXMATRIXA16 world;

	static const int TRIANGLE_COUNT = 12;
	TextureTriangle triangles[TRIANGLE_COUNT];

};

