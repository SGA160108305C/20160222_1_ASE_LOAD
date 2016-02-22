#pragma once
#include "GameState.h"
#include "Grid.h"
#include "CubeMan.h"

class GameState_HierarchyAnimation :
	public GameState
{
public:
	GameState_HierarchyAnimation();
	virtual ~GameState_HierarchyAnimation();

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
	CubeMan* cubeMan = nullptr;
};

