#include "stdafx.h"
#include "GameState_DX_Base.h"


GameState_DX_Base::GameState_DX_Base()
{
}


GameState_DX_Base::~GameState_DX_Base()
{
}

void GameState_DX_Base::Initialize()
{
	Reset();
}

void GameState_DX_Base::Destroy()
{
}

void GameState_DX_Base::Reset()
{
}

void GameState_DX_Base::Update()
{
}

void GameState_DX_Base::Render()
{
}

void GameState_DX_Base::OnEnterState()
{
	Initialize();
}

void GameState_DX_Base::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_DX_Base::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
