#include "stdafx.h"
#include "GameState_Texture.h"


GameState_Texture::GameState_Texture()
{
}


GameState_Texture::~GameState_Texture()
{
}

void GameState_Texture::Initialize()
{
	cube = new Cube_Texture();
	cube->Initialize();

	GameManager::GetCamera()->SetLookTarget(cube->GetPositionAdress());

	D3DXFONT_DESC font_desc;
	ZeroMemory(&font_desc, sizeof(D3DXFONT_DESC));
	font_desc.Height = 50;
	font_desc.Width = 25;
	font_desc.Weight = FW_NORMAL;
	font_desc.MipLevels = D3DX_DEFAULT;
	font_desc.Italic = false;
	font_desc.CharSet = DEFAULT_CHARSET;
	font_desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	font_desc.Quality = DEFAULT_QUALITY;
	font_desc.PitchAndFamily = FF_DONTCARE;
	wcscpy_s(font_desc.FaceName, L"휴먼편지체");	//글꼴 스타일
	//AddFontResource(L"./Data/Font/umberto.ttf");
	//wcscpy_s(font_desc.FaceName, L"umberto");

	D3DXCreateFontIndirect(
		GameManager::GetDevice(),
		&font_desc,
		&font);
		
}
void GameState_Texture::Destroy()
{
	SAFE_RELEASE(font);
	SAFE_DELETE(cube);
}

void GameState_Texture::Update()
{
	if (cube)
	{
		cube->Update();
	}
}
void GameState_Texture::Render()
{
	if (cube)
	{
		cube->Render();
	}

	if (font)
	{
		RECT rc = { 10, 10, 11, 11 };
		font->DrawTextA(
			NULL,
			"가나다 AAA",
			strlen("가나다 AAA"),
			&rc,
			DT_TOP|DT_LEFT|DT_NOCLIP,
			D3DCOLOR_XRGB(255,255,255));
	}
}
void GameState_Texture::OnEnterState()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	Initialize();
	
}
void GameState_Texture::OnLeaveState()
{
	Destroy();
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

LRESULT GameState_Texture::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


void GameState_Texture::Reset()
{

}