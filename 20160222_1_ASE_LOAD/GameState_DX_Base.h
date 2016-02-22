#pragma once
#include "GameState.h"
class GameState_DX_Base :
	public GameState
{
public:
	GameState_DX_Base();
	virtual ~GameState_DX_Base();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Reset() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
};

