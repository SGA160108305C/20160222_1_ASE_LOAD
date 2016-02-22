#include "stdafx.h"
#include "GameState_Picking.h"


GameState_Picking::GameState_Picking()
{
}


GameState_Picking::~GameState_Picking()
{
}

void GameState_Picking::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}	
	if ( objBox == nullptr )
	{
		objBox = new Obj();
		objBox->Initialize("Box.obj");
		objBox->SetPosition(D3DXVECTOR3(10, 0, 10));
	}
	if ( objMap == nullptr )
	{
		objMap = new Obj();
		objMap->Initialize("map.obj", "map_surface.obj");		
	}
	if ( cubeMan == nullptr )
	{
		cubeMan = new CubeMan_Walk;
		cubeMan->Initialize();
		cubeMan->SetPosition(D3DXVECTOR3(-1, 0, -1));
		cubeMan->SetWalkingMap(objMap);
	}
	Reset();
}

void GameState_Picking::Destroy()
{
	SAFE_DELETE(cubeMan);
	SAFE_DELETE(objMap);
	SAFE_DELETE(objBox);	
	SAFE_DELETE(grid);	
}

void GameState_Picking::Reset()
{
}

void GameState_Picking::Update()
{
	if ( cubeMan )
	{
		cubeMan->Update();
	}
	if ( objBox )
	{
		objBox->Update();
	}
}

void GameState_Picking::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( objMap )
	{
		objMap->Render();
	}
	if ( objBox )
	{
		objBox->Render();
	}
	if ( cubeMan )
	{
		cubeMan->Render();
	}

}

void GameState_Picking::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(20.0f);
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cubeMan->GetPositionAdress());
}

void GameState_Picking::OnLeaveState()
{
	Destroy();
}

LRESULT GameState_Picking::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cubeMan )
	{
		cubeMan->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
