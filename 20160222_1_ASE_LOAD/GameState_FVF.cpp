#include "stdafx.h"
#include "GameState_FVF.h"


GameState_FVF::GameState_FVF()
{
}

GameState_FVF::~GameState_FVF()
{
}

void GameState_FVF::Initialize()
{

}

void GameState_FVF::Destroy()
{

}

void GameState_FVF::Update()
{
}

void GameState_FVF::Render()
{
	D3DXMATRIXA16 world, rot, trans;
	D3DXMatrixIdentity(&world);
	D3DXMatrixRotationZ(&rot, D3DXToRadian(80.0f));
	world *= rot;
	D3DXMatrixTranslation(&trans, 2, 0, 0);
	world *= trans;
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	
	GameManager::GetDevice()->SetTexture(0, nullptr);
	//GameManager::GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	FVF_PositionColor vertex[3];
	vertex[0].pos = D3DXVECTOR3(0, 0, 0);
	vertex[0].color = D3DCOLOR_XRGB(255, 0, 0);
	vertex[1].pos = D3DXVECTOR3(0, 1, 0);
	vertex[1].color = D3DCOLOR_XRGB(0, 255, 0);
	vertex[2].pos = D3DXVECTOR3(1, 0, 0);
	vertex[2].color = D3DCOLOR_XRGB(0, 0, 255);

	
	GameManager::GetDevice()->SetFVF(FVF_PositionColor::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		1,
		vertex,
		sizeof(FVF_PositionColor));

	D3DXMatrixIdentity(&world);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	FVF_PositionColor lineVertex[4];
	lineVertex[0].pos = D3DXVECTOR3(10, 0, 0);
	lineVertex[0].color = D3DCOLOR_XRGB(255, 0, 0);
	lineVertex[1].pos = D3DXVECTOR3(10, 10, 0);
	lineVertex[1].color = D3DCOLOR_XRGB(0, 255, 0);
	lineVertex[2].pos = D3DXVECTOR3(20, 10, 0);
	lineVertex[2].color = D3DCOLOR_XRGB(0, 0, 255);
	lineVertex[3].pos = D3DXVECTOR3(20, 0, 0);
	lineVertex[3].color = D3DCOLOR_XRGB(0, 0, 255);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_LINELIST,
		2,
		lineVertex,
		sizeof(FVF_PositionColor));
	
	
	
	FVF_PositionColorTexture vertexT[3];
	vertexT[0].pos = D3DXVECTOR3(-2, 0, 0);
	vertexT[0].color = D3DCOLOR_XRGB(255, 0, 0);
	vertexT[0].tex = D3DXVECTOR2(0, 1);
	vertexT[1].pos = D3DXVECTOR3(-1, 1, 0);
	vertexT[1].color = D3DCOLOR_XRGB(0, 255, 0);
	vertexT[1].tex = D3DXVECTOR2(1, 0);
	vertexT[2].pos = D3DXVECTOR3(-1, 0, 0);
	vertexT[2].color = D3DCOLOR_XRGB(0, 0, 255);
	vertexT[2].tex = D3DXVECTOR2(1, 1);
	GameManager::GetDevice()->SetTexture(0, texture);
	GameManager::GetDevice()->SetFVF(FVF_PositionColorTexture::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		1,
		vertexT,
		sizeof(FVF_PositionColorTexture));
	
}

void GameState_FVF::OnEnterState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	D3DXCreateTextureFromFile(
		GameManager::GetDevice(),
		L"./Data/Texture/Box.jpg",
		&texture);
}

void GameState_FVF::OnLeaveState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	SAFE_RELEASE(texture);
}

LRESULT GameState_FVF::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void GameState_FVF::Reset()
{

}