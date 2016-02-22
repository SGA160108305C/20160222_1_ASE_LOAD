#pragma once
#include "GameState.h"
class GameState_FVF :
	public GameState
{
public:
	GameState_FVF();
	virtual ~GameState_FVF();

	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	virtual void Reset() override;

	LPDIRECT3DTEXTURE9 texture = nullptr;
};

