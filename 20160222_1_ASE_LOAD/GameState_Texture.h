#pragma once
#include "GameState.h"
#include "Cube_Texture.h"

class GameState_Texture :
	public GameState
{
public:
	GameState_Texture();
	virtual ~GameState_Texture();

	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	virtual void Reset() override;

	Cube_Texture* cube = nullptr;

	LPD3DXFONT font = nullptr;
};

