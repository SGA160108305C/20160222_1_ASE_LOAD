#include "stdafx.h"
#include "GameState_HierarchyAnimation.h"


GameState_HierarchyAnimation::GameState_HierarchyAnimation()
{
}


GameState_HierarchyAnimation::~GameState_HierarchyAnimation()
{
}

void GameState_HierarchyAnimation::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}
	if ( cubeMan == nullptr )
	{
		cubeMan = new CubeMan;
		cubeMan->Initialize();
	}
	Reset();
}

void GameState_HierarchyAnimation::Destroy()
{
	SAFE_DELETE(cubeMan);
	SAFE_DELETE(grid);	
}

void GameState_HierarchyAnimation::Reset()
{
}

void GameState_HierarchyAnimation::Update()
{
	if ( cubeMan )
	{
		cubeMan->Update();
	}
}

void GameState_HierarchyAnimation::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( cubeMan )
	{
		cubeMan->Render();
	}

}

void GameState_HierarchyAnimation::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(30.0f);
	
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cubeMan->GetPositionAdress());
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
}

void GameState_HierarchyAnimation::OnLeaveState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	Destroy();
}

LRESULT GameState_HierarchyAnimation::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cubeMan )
	{
		cubeMan->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
