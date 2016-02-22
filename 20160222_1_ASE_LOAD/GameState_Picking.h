#pragma once
#include "GameState.h"
#include "Grid.h"
#include "CubeMan_Walk.h"
#include "Obj.h"

class GameState_Picking :
	public GameState
{
public:
	GameState_Picking();
	virtual ~GameState_Picking();

	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Reset() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnEnterState() override;
	virtual void OnLeaveState() override;

	virtual LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	Grid* grid = nullptr;
	CubeMan_Walk* cubeMan = nullptr;

	Obj* objMap = nullptr;
	Obj* objBox = nullptr;
};

