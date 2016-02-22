#include "stdafx.h"
#include "CubeMan_Walk.h"


CubeMan_Walk::CubeMan_Walk()
{
}


CubeMan_Walk::~CubeMan_Walk()
{
}

void CubeMan_Walk::Destroy()
{
	CubeMan_Light::Destroy();
	walkingMap = nullptr;
}

void CubeMan_Walk::Update()
{
	GameObject::Update();

	float tick = (float)GameManager::GetTick();
	jumpTime += tick;
	if ((GetAsyncKeyState('A') & 0x8000) != 0)
	{
		rotationAngle -= (rotationSpeed * tick);
	}
	else if ((GetAsyncKeyState('D') & 0x8000) != 0)
	{
		rotationAngle += (rotationSpeed * tick);
	}

	if ((GetAsyncKeyState('W') & 0x8000) != 0)
	{
		if (walkingMap)
		{
			D3DXVECTOR3 newPosition = position + (direction * moveSpeed * tick);
			if (walkingMap->GroundCheck(newPosition))
			{
				position = newPosition;
			}
		}
		//position += (direction * moveSpeed * tick);

		bool wasPressed = keyState[FORWARD];
		if (wasPressed == false)
		{
			//Ã³À½ ´­·¶´Ù.
			AnimationOnOff(true);
		}
		keyState[FORWARD] = true;
	}
	else
	{
		bool wasPressed = keyState[FORWARD];
		if (wasPressed == true)
		{
			//Å°¸¦ ¶© Á÷ÈÄ´Ù
			AnimationOnOff(false);
		}
		keyState[FORWARD] = false;
	}

	if ((GetAsyncKeyState('S') & 0x8000) != 0)
	{
		if (walkingMap)
		{
			D3DXVECTOR3 newPosition = position - (direction * moveSpeed * tick);
			if (walkingMap->GroundCheck(newPosition))
			{
				position = newPosition;
			}
		}

		bool wasPressed = keyState[BACKWARD];
		if (wasPressed == false)
		{
			//Ã³À½ ´­·¶´Ù.
			AnimationOnOff(true);
		}
		keyState[BACKWARD] = true;
	}
	else
	{
		bool wasPressed = keyState[BACKWARD];
		if (wasPressed == true)
		{
			//Å°¸¦ ¶© Á÷ÈÄ´Ù
			AnimationOnOff(false);
		}
		keyState[BACKWARD] = false;
	}

	if ((GetAsyncKeyState('N') & 0x8000) != 0)
	{
		SetNextTexture();
	}
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0 && isJumping == false)
	{
		isJumping = true;
		jumpTime = 0.0f;
		jumpStart = position.y;
	}

	D3DXMATRIX scale, rotation, translation;
	D3DXMatrixScaling(&scale, scaleVector.x, scaleVector.y, scaleVector.z);
	D3DXMatrixRotationY(&rotation, rotationAngle);

	world = scale * rotation;

	D3DXVECTOR3 baseDirection(0, 0, 1);
	D3DXVec3TransformCoord(&direction, &baseDirection, &world);

	if (isJumping)
	{
		position.y = jumpStart + jumpPower * jumpTime - 4.9f/*0.5f * ( 9.8f ) */* jumpTime * jumpTime;

		D3DXVECTOR3 newHeight = position;
		if (walkingMap)
		{
			walkingMap->GroundCheck(newHeight);
		}
		else
		{
			newHeight.y = 0.0f;
		}

		if (position.y < newHeight.y)
		{
			isJumping = false;
			jumpStart = 0.0f;
			position.y = newHeight.y;
		}
	}


	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);
	world *= translation;

	root->Update(&world);
}