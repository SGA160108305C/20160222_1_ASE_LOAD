#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Obj.h"

class GameState_OBJ_Load :
	public GameState
{
public:
	GameState_OBJ_Load();
	virtual ~GameState_OBJ_Load();

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

	Obj* objMap = nullptr;
	Obj* objBox = nullptr;
};

