#include "stdafx.h"
#include "CubeMan.h"


CubeMan::CubeMan()
{
}

CubeMan::~CubeMan()
{
	Destroy();
}

void CubeMan::Initialize()
{
	D3DXMatrixIdentity(&world);
	ZeroMemory(keyState, sizeof(bool)*NUM_OF_KEY_TYPE);

	D3DXVECTOR2 uvList[36];

	root = new CubeManParts;
	GetCubeUVList(uvList, BODY);
	root->Initialize(D3DXVECTOR3(1.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 3.0f, 0.0f));
	root->SetTextureUV(uvList);

	CubeManParts* head = new CubeManParts;
	GetCubeUVList(uvList, HEAD);
	head->Initialize(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	head->SetTextureUV(uvList);
	root->AddChild(head);

	CubeManParts* leftArm = new CubeManParts;
	GetCubeUVList(uvList, LEFT_ARM);
	leftArm->Initialize(D3DXVECTOR3(0.5f, 2.0f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(-0.8f, 1.0f, 0.0f));
	leftArm->SetTextureUV(uvList);
	leftArm->SetRotationSpeed(2.0f);
	root->AddChild(leftArm);
	animParts[LEFT_ARM] = leftArm;

	CubeManParts* rightArm = new CubeManParts;
	GetCubeUVList(uvList, RIGHT_ARM);
	rightArm->Initialize(D3DXVECTOR3(0.5f, 2.0f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.8f, 1.0f, 0.0f));
	rightArm->SetTextureUV(uvList);
	rightArm->SetRotationSpeed(-2.0f);
	root->AddChild(rightArm);
	animParts[RIGHT_ARM] = rightArm;

	CubeManParts* leftLeg = new CubeManParts;
	GetCubeUVList(uvList, LEFT_LEG);
	leftLeg->Initialize(D3DXVECTOR3(0.5f, 2.0f, 0.8f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(-0.3f, -1.0f, 0.0f));
	leftLeg->SetTextureUV(uvList);
	leftLeg->SetRotationSpeed(-2.0f);
	root->AddChild(leftLeg);
	animParts[LEFT_LEG] = leftLeg;

	CubeManParts* rigthLeg = new CubeManParts;
	GetCubeUVList(uvList, RIGHT_LEG);
	rigthLeg->Initialize(D3DXVECTOR3(0.5f, 2.0f, 0.8f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.3f, -1.0f, 0.0f));
	rigthLeg->SetTextureUV(uvList);
	rigthLeg->SetRotationSpeed(2.0f);
	root->AddChild(rigthLeg);
	animParts[RIGHT_LEG] = rigthLeg;

	texture[BATMAN] = TextureManager::GetTexture("batman.png");
	texture[IRONMAN] = TextureManager::GetTexture("IronMan.png");
	texture[ROBOCAP] = TextureManager::GetTexture("robocop.png");
	texture[SPIDERMAN] = TextureManager::GetTexture("spiderman.png");

	AnimationOnOff(false);
}

void CubeMan::Destroy()
{
	GameObject::Destroy();

	SAFE_DELETE(root);

	texture[BATMAN] = nullptr;
	texture[IRONMAN] = nullptr;
	texture[ROBOCAP] = nullptr;
	texture[SPIDERMAN] = nullptr;
}

void CubeMan::Update()
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
		position += (direction * moveSpeed * tick);

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
		position -= (direction * moveSpeed * tick);

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

		if (position.y < 0.0f)
		{
			isJumping = false;
			jumpStart = 0.0f;
			position.y = 0.0f;
		}
	}

	D3DXMatrixTranslation(&translation, position.x, position.y, position.z);
	world *= translation;

	root->Update(&world);
}

void CubeMan::Render()
{
	GameManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	GameManager::GetDevice()->SetTexture(0, texture[currentTexture]);
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionTexture::FVF);
	root->Render();
}

LRESULT CubeMan::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		//result = WM_LBUTTONDOWN;
	}
	break;
	case WM_LBUTTONUP:
	{
		//result = WM_LBUTTONUP;
	}
	break;
	case WM_MOUSEMOVE:
	{
		//result = WM_MOUSEMOVE;
	}
	break;
	}
	return result;
}

bool CubeMan::GetCubeUVList(D3DXVECTOR2* out, PartsType type)
{
	bool returnVal = true;

	switch (type)
	{
	case BODY:
	{
		out[0] = D3DXVECTOR2(0.3125f, 1.0f); out[1] = D3DXVECTOR2(0.3125f, 0.625f); out[2] = D3DXVECTOR2(0.4375f, 0.625f);
		out[3] = D3DXVECTOR2(0.3125f, 1.0f); out[4] = D3DXVECTOR2(0.4375f, 0.625f); out[5] = D3DXVECTOR2(0.4375f, 1.0f);
		out[6] = D3DXVECTOR2(0.25f, 1.0f); out[7] = D3DXVECTOR2(0.25f, 0.625f); out[8] = D3DXVECTOR2(0.3125f, 0.625f);
		out[9] = D3DXVECTOR2(0.25f, 1.0f); out[10] = D3DXVECTOR2(0.3125f, 0.625f); out[11] = D3DXVECTOR2(0.3125f, 1.0f);
		out[12] = D3DXVECTOR2(0.5f, 1.0f); out[13] = D3DXVECTOR2(0.5f, 0.625f); out[14] = D3DXVECTOR2(0.625f, 0.625f);
		out[15] = D3DXVECTOR2(0.5f, 1.0f); out[16] = D3DXVECTOR2(0.625f, 0.625f); out[17] = D3DXVECTOR2(0.625f, 1.0f);
		out[18] = D3DXVECTOR2(0.4375f, 1.0f); out[19] = D3DXVECTOR2(0.4375f, 0.625f); out[20] = D3DXVECTOR2(0.5f, 0.625f);
		out[21] = D3DXVECTOR2(0.4375f, 1.0f); out[22] = D3DXVECTOR2(0.5f, 0.625f); out[23] = D3DXVECTOR2(0.5f, 1.0f);
		out[24] = D3DXVECTOR2(0.315f, 0.625f); out[25] = D3DXVECTOR2(0.3125f, 0.5f); out[26] = D3DXVECTOR2(0.4375f, 0.5f);
		out[27] = D3DXVECTOR2(0.315f, 0.625f); out[28] = D3DXVECTOR2(0.4375f, 0.5f); out[29] = D3DXVECTOR2(0.4375f, 0.625f);
		out[30] = D3DXVECTOR2(0.4375f, 0.625f); out[31] = D3DXVECTOR2(0.4375f, 0.5f); out[32] = D3DXVECTOR2(0.5626f, 0.5f);
		out[33] = D3DXVECTOR2(0.4375f, 0.625f); out[34] = D3DXVECTOR2(0.5626f, 0.5f); out[35] = D3DXVECTOR2(0.5626f, 0.625f);
	}
	break;
	case HEAD:
	{
		out[0] = D3DXVECTOR2(0.125, 0.5); out[1] = D3DXVECTOR2(0.125, 0.25); out[2] = D3DXVECTOR2(0.25, 0.25);
		out[3] = D3DXVECTOR2(0.125, 0.5); out[4] = D3DXVECTOR2(0.25, 0.25); out[5] = D3DXVECTOR2(0.25, 0.5);
		out[6] = D3DXVECTOR2(0.0, 0.5); out[7] = D3DXVECTOR2(0.0, 0.25); out[8] = D3DXVECTOR2(0.125, 0.25);
		out[9] = D3DXVECTOR2(0.0, 0.5); out[10] = D3DXVECTOR2(0.125, 0.25); out[11] = D3DXVECTOR2(0.125, 0.5);
		out[12] = D3DXVECTOR2(0.375, 0.5); out[13] = D3DXVECTOR2(0.375, 0.25); out[14] = D3DXVECTOR2(0.5, 0.25);
		out[15] = D3DXVECTOR2(0.375, 0.5); out[16] = D3DXVECTOR2(0.5, 0.25); out[17] = D3DXVECTOR2(0.5, 0.5);
		out[18] = D3DXVECTOR2(0.25, 0.5); out[19] = D3DXVECTOR2(0.25, 0.25); out[20] = D3DXVECTOR2(0.375, 0.25);
		out[21] = D3DXVECTOR2(0.25, 0.5); out[22] = D3DXVECTOR2(0.375, 0.25); out[23] = D3DXVECTOR2(0.375, 0.5);
		out[24] = D3DXVECTOR2(0.125, 0.25); out[25] = D3DXVECTOR2(0.125, 0); out[26] = D3DXVECTOR2(0.25, 0);
		out[27] = D3DXVECTOR2(0.125, 0.25); out[28] = D3DXVECTOR2(0.25, 0); out[29] = D3DXVECTOR2(0.25, 0.25);
		out[30] = D3DXVECTOR2(0.25, 0.25); out[31] = D3DXVECTOR2(0.25, 0); out[32] = D3DXVECTOR2(0.375, 0);
		out[33] = D3DXVECTOR2(0.25, 0.25); out[34] = D3DXVECTOR2(0.375, 0); out[35] = D3DXVECTOR2(0.375, 0.25);
	}
	break;
	case LEFT_ARM:
	{
		out[0] = D3DXVECTOR2(0.75, 1); out[1] = D3DXVECTOR2(0.75, 0.625); out[2] = D3DXVECTOR2(0.6875, 0.625);
		out[3] = D3DXVECTOR2(0.75, 1); out[4] = D3DXVECTOR2(0.6875, 0.625); out[5] = D3DXVECTOR2(0.6875, 1);
		out[6] = D3DXVECTOR2(0.8125, 1); out[7] = D3DXVECTOR2(0.8125, 0.5); out[8] = D3DXVECTOR2(0.75, 0.625);
		out[9] = D3DXVECTOR2(0.8125, 1); out[10] = D3DXVECTOR2(0.75, 0.625); out[11] = D3DXVECTOR2(0.75, 1);
		out[12] = D3DXVECTOR2(0.875, 1); out[13] = D3DXVECTOR2(0.875, 0.625); out[14] = D3DXVECTOR2(0.8125, 0.625);
		out[15] = D3DXVECTOR2(0.875, 1); out[16] = D3DXVECTOR2(0.8125, 0.625); out[17] = D3DXVECTOR2(0.8125, 1);
		out[18] = D3DXVECTOR2(0.6875, 1); out[19] = D3DXVECTOR2(0.6875, 0.625); out[20] = D3DXVECTOR2(0.625, 0.625);
		out[21] = D3DXVECTOR2(0.6875, 1); out[22] = D3DXVECTOR2(0.625, 0.625); out[23] = D3DXVECTOR2(0.625, 1);
		out[24] = D3DXVECTOR2(0.75, 0.625); out[25] = D3DXVECTOR2(0.75, 0.5); out[26] = D3DXVECTOR2(0.6875, 0.5);
		out[27] = D3DXVECTOR2(0.75, 0.625); out[28] = D3DXVECTOR2(0.6875, 0.5); out[29] = D3DXVECTOR2(0.6875, 0.625);
		out[30] = D3DXVECTOR2(0.8125, 0.625); out[31] = D3DXVECTOR2(0.8125, 0.5); out[32] = D3DXVECTOR2(0.75, 0.5);
		out[33] = D3DXVECTOR2(0.8125, 0.625); out[34] = D3DXVECTOR2(0.75, 0.5); out[35] = D3DXVECTOR2(0.75, 0.625);
	}
	break;
	case RIGHT_ARM:
	{
		out[0] = D3DXVECTOR2(0.6875, 1); out[1] = D3DXVECTOR2(0.6875, 0.625); out[2] = D3DXVECTOR2(0.75, 0.625);
		out[3] = D3DXVECTOR2(0.6875, 1); out[4] = D3DXVECTOR2(0.75, 0.625); out[5] = D3DXVECTOR2(0.75, 1);
		out[6] = D3DXVECTOR2(0.625, 1); out[7] = D3DXVECTOR2(0.625, 0.625); out[8] = D3DXVECTOR2(0.6875, 0.625);
		out[9] = D3DXVECTOR2(0.625, 1); out[10] = D3DXVECTOR2(0.6875, 0.625); out[11] = D3DXVECTOR2(0.6875, 1);
		out[12] = D3DXVECTOR2(0.8125, 1); out[13] = D3DXVECTOR2(0.8125, 0.625); out[14] = D3DXVECTOR2(0.875, 0.625);
		out[15] = D3DXVECTOR2(0.8125, 1); out[16] = D3DXVECTOR2(0.875, 0.625); out[17] = D3DXVECTOR2(0.875, 1);
		out[18] = D3DXVECTOR2(0.75, 1); out[19] = D3DXVECTOR2(0.75, 0.5); out[20] = D3DXVECTOR2(0.8125, 0.625);
		out[21] = D3DXVECTOR2(0.75, 1); out[22] = D3DXVECTOR2(0.8125, 0.625); out[23] = D3DXVECTOR2(0.8125, 1);
		out[24] = D3DXVECTOR2(0.6875, 0.625); out[25] = D3DXVECTOR2(0.6875, 0.5); out[26] = D3DXVECTOR2(0.75, 0.5);
		out[27] = D3DXVECTOR2(0.6875, 0.625); out[28] = D3DXVECTOR2(0.75, 0.5); out[29] = D3DXVECTOR2(0.75, 0.625);
		out[30] = D3DXVECTOR2(0.75, 0.625); out[31] = D3DXVECTOR2(0.75, 0.5); out[32] = D3DXVECTOR2(0.8125, 0.5);
		out[33] = D3DXVECTOR2(0.75, 0.625); out[34] = D3DXVECTOR2(0.8125, 0.5); out[35] = D3DXVECTOR2(0.8125, 0.625);
	}
	break;
	case LEFT_LEG:
	{
		out[0] = D3DXVECTOR2(0.125, 1); out[1] = D3DXVECTOR2(0.125, 0.625); out[2] = D3DXVECTOR2(0.0625, 0.625);
		out[3] = D3DXVECTOR2(0.125, 1); out[4] = D3DXVECTOR2(0.0625, 0.625); out[5] = D3DXVECTOR2(0.0625, 1);
		out[6] = D3DXVECTOR2(0.1875, 1); out[7] = D3DXVECTOR2(0.1875, 0.625); out[8] = D3DXVECTOR2(0.125, 0.625);
		out[9] = D3DXVECTOR2(0.1875, 1); out[10] = D3DXVECTOR2(0.125, 0.625); out[11] = D3DXVECTOR2(0.125, 1);
		out[12] = D3DXVECTOR2(0.25, 1); out[13] = D3DXVECTOR2(0.25, 0.625); out[14] = D3DXVECTOR2(0.1875, 0.625);
		out[15] = D3DXVECTOR2(0.25, 1); out[16] = D3DXVECTOR2(0.1875, 0.625); out[17] = D3DXVECTOR2(0.1875, 1);
		out[18] = D3DXVECTOR2(0.0625, 1); out[19] = D3DXVECTOR2(0.0625, 0.625); out[20] = D3DXVECTOR2(0, 0.625);
		out[21] = D3DXVECTOR2(0.0625, 1); out[22] = D3DXVECTOR2(0, 0.625); out[23] = D3DXVECTOR2(0, 1);
		out[24] = D3DXVECTOR2(0.125, 0.625); out[25] = D3DXVECTOR2(0.125, 0.5); out[26] = D3DXVECTOR2(0.0625, 0.5);
		out[27] = D3DXVECTOR2(0.125, 0.625); out[28] = D3DXVECTOR2(0.0625, 0.5); out[29] = D3DXVECTOR2(0.0625, 0.625);
		out[30] = D3DXVECTOR2(0.1875, 0.625); out[31] = D3DXVECTOR2(0.1875, 0.5); out[32] = D3DXVECTOR2(0.125, 0.5);
		out[33] = D3DXVECTOR2(0.1875, 0.625); out[34] = D3DXVECTOR2(0.125, 0.5); out[35] = D3DXVECTOR2(0.125, 0.625);
	}
	break;
	case RIGHT_LEG:
	{
		out[0] = D3DXVECTOR2(0.0625, 1); out[1] = D3DXVECTOR2(0.0625, 0.625); out[2] = D3DXVECTOR2(0.125, 0.625);
		out[3] = D3DXVECTOR2(0.0625, 1); out[4] = D3DXVECTOR2(0.125, 0.625); out[5] = D3DXVECTOR2(0.125, 1);
		out[6] = D3DXVECTOR2(0, 1); out[7] = D3DXVECTOR2(0, 0.625); out[8] = D3DXVECTOR2(0.0625, 0.625);
		out[9] = D3DXVECTOR2(0, 1); out[10] = D3DXVECTOR2(0.0625, 0.625); out[11] = D3DXVECTOR2(0.0625, 1);
		out[12] = D3DXVECTOR2(0.1875, 1); out[13] = D3DXVECTOR2(0.1875, 0.625); out[14] = D3DXVECTOR2(0.25, 0.625);
		out[15] = D3DXVECTOR2(0.1875, 1); out[16] = D3DXVECTOR2(0.25, 0.625); out[17] = D3DXVECTOR2(0.25, 1);
		out[18] = D3DXVECTOR2(0.125, 1); out[19] = D3DXVECTOR2(0.125, 0.625); out[20] = D3DXVECTOR2(0.1875, 0.625);
		out[21] = D3DXVECTOR2(0.125, 1); out[22] = D3DXVECTOR2(0.1875, 0.625); out[23] = D3DXVECTOR2(0.1875, 1);
		out[24] = D3DXVECTOR2(0.0625, 0.625); out[25] = D3DXVECTOR2(0.0625, 0.5); out[26] = D3DXVECTOR2(0.125, 0.5);
		out[27] = D3DXVECTOR2(0.0625, 0.625); out[28] = D3DXVECTOR2(0.125, 0.5); out[29] = D3DXVECTOR2(0.125, 0.625);
		out[30] = D3DXVECTOR2(0.125, 0.625); out[31] = D3DXVECTOR2(0.125, 0.5); out[32] = D3DXVECTOR2(0.1875, 0.5);
		out[33] = D3DXVECTOR2(0.125, 0.625); out[34] = D3DXVECTOR2(0.1875, 0.5); out[35] = D3DXVECTOR2(0.1875, 0.625);
	}
	break;

	default:
		returnVal = false;
		break;
	}

	return returnVal;
}

void CubeMan::SetNextTexture()
{
	int temp = currentTexture;
	temp++;
	temp = temp % NUM_OF_TEXTURETYPE;
	currentTexture = (TextureType)temp;
}

void CubeMan::AnimationOnOff(bool on)
{
	if (on)
	{
		animParts[LEFT_ARM]->SetRotationSpeed(2.0f);
		animParts[RIGHT_ARM]->SetRotationSpeed(-2.0f);
		animParts[LEFT_LEG]->SetRotationSpeed(-2.0f);
		animParts[RIGHT_LEG]->SetRotationSpeed(2.0f);
	}
	else
	{
		animParts[LEFT_ARM]->StopRotationX();
		animParts[RIGHT_ARM]->StopRotationX();
		animParts[LEFT_LEG]->StopRotationX();
		animParts[RIGHT_LEG]->StopRotationX();
	}
}