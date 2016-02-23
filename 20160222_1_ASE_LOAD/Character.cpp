#include "stdafx.h"
#include "Character.h"
#include "AseLoader.h"

Character::Character()
{
}


Character::~Character()
{
}

void Character::Initialize()
{
	AseLoader ase;
	aseRootFrame = ase.Load("woman_01_all.ASE");
	aseRootFrame->SetTextureOn(true);

	D3DXMatrixIdentity(&world);
}

void Character::Destroy()
{
	SAFE_DELETE(aseRootFrame);
	GameObject::Destroy();
}

void Character::Update()
{
	float tick = (float)GameManager::GetTick();

	D3DXMatrixIdentity(&world);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, rotationAngle + BASE_ANGLE);
	world *= rotation;

	D3DXVECTOR3 baseDirection(0, 0, 1);
	D3DXVec3TransformCoord(&direction, &baseDirection, &world);

	rotationAngle -= (rotationSpeed * tick);
	position -= (direction * moveSpeed * tick);

	//이동 처리
	if ( ( GetAsyncKeyState('A') & 0x8000 ) != 0 )
	{
		rotationAngle -= ( rotationSpeed * tick );
	}
	else if ( ( GetAsyncKeyState('D') & 0x8000 ) != 0 )
	{
		rotationAngle += ( rotationSpeed * tick );
	}
	if ( ( GetAsyncKeyState('W') & 0x8000 ) != 0 )
	{
		position -= ( direction * moveSpeed * tick );		
	}
	else if ( ( GetAsyncKeyState('S') & 0x8000 ) != 0 )
	{
		position += ( direction * moveSpeed * tick );		
	}

	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, position.x + 1.0f, position.y, position.z);
	world *= translation;
	
	if ( aseRootFrame )
	{
		int keyFrame = GetTickCount() % ( 3200 - 640 ) + 640;
		aseRootFrame->Update(keyFrame, &world);
	}
	GameObject::Update();
	
}

void Character::Render()
{
	if ( aseRootFrame )
	{
		aseRootFrame->Render();
	}
}

LRESULT Character::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}