#include "stdafx.h"
#include "GameState_Light.h"


GameState_Light::GameState_Light()
{
}


GameState_Light::~GameState_Light()
{
}

void GameState_Light::Initialize()
{
	if ( grid == nullptr )
	{
		grid = new Grid;
		grid->Initialize();
	}
	if ( cube == nullptr )
	{
		cube = new Cube_Material;
		cube->Initialize(D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(3, 0, 0));
	}
	if ( cubeMan == nullptr )
	{
		cubeMan = new CubeMan_Light;
		cubeMan->Initialize();
	}
	Reset();
}

void GameState_Light::Destroy()
{
	SAFE_DELETE(cubeMan);
	SAFE_DELETE(cube);
	SAFE_DELETE(grid);	
}

void GameState_Light::Reset()
{
}

void GameState_Light::Update()
{
	if (cube)
	{
		cube->Update();
	}
	if ( cubeMan )
	{
		cubeMan->Update();
	}
}

void GameState_Light::Render()
{
	if ( grid )
	{
		grid->Render();
	}
	if ( cubeMan )
	{
		cubeMan->Render();
	}
	if (cube)
	{
		cube->Render();
	}

}

void GameState_Light::OnEnterState()
{
	GameManager::GetCamera()->SetDistance(30.0f);
	
	Initialize();
	GameManager::GetCamera()->SetLookTarget(cubeMan->GetPositionAdress());
	//GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(-1,-2,-1);
	light.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	GameManager::GetDevice()->SetLight(0, &light);
	GameManager::GetDevice()->LightEnable(0, true);
}

void GameState_Light::OnLeaveState()
{
	//GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	Destroy();
}

LRESULT GameState_Light::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if ( result == 0 && cubeMan )
	{
		cubeMan->InputProc(hWnd, message, wParam, lParam);
	}
	return result;
}
