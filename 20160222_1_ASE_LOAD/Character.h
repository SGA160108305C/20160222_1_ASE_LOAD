#pragma once
#include "GameObject.h"
#include "AseFrame.h"

class Character :
	public GameObject
{
public:
	Character();
	virtual ~Character();

	virtual void Initialize();
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	D3DXMATRIXA16 world;
	AseFrame* aseRootFrame = nullptr;

	bool textureOn = false;

	const float BASE_ANGLE = D3DX_PI;

	float moveSpeed = 1.0f;
	float rotationSpeed = 0.5f;

	bool keyWasPressed = false;	//스페이스만 체크
};

