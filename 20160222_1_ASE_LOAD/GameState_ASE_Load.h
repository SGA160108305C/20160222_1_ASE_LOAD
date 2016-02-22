#pragma once
#include "GameState.h"
#include "Grid.h"
#include "Character.h"

class GameState_ASE_Load :
	public GameState
{
public:
	GameState_ASE_Load();
	virtual ~GameState_ASE_Load();

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
	Character* girl = nullptr;
};

