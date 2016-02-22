#pragma once
#include "GameObject.h"
#include "CubeManParts.h"

enum PartsType
{
	BODY,
	HEAD,
	LEFT_ARM,
	RIGHT_ARM,
	LEFT_LEG,
	RIGHT_LEG
};

enum TextureType
{
	BATMAN = 0,
	IRONMAN,
	ROBOCAP,
	SPIDERMAN,
	NUM_OF_TEXTURETYPE
};

class CubeMan : public GameObject
{
public:
	CubeMan();
	~CubeMan();

	void Initialize();
	virtual void Destroy() override;
	virtual void Render() override;
	virtual void Update() override;

	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	inline const LPD3DXVECTOR3 GetPositionAdress(){ return &position; }

	void SetNextTexture();

protected:
	enum KEY_TYPE
	{
		FORWARD = 0,
		BACKWARD,
		NUM_OF_KEY_TYPE
	};
	D3DXMATRIXA16 world;
	CubeManParts* root = nullptr;
	LPDIRECT3DTEXTURE9 texture[NUM_OF_TEXTURETYPE];
	TextureType currentTexture = TextureType::BATMAN;

	//위치와 이동, 회전, 스케일
	float moveSpeed = 10.0f;
	float rotationSpeed = 2.0f;
	D3DXVECTOR3 scaleVector = D3DXVECTOR3(1, 1, 1);

	//점프
	float jumpPower = 10.0f;
	float jumpTime = 0.0f;
	bool isJumping = false;
	float jumpStart = 0.0f;

	//키 상태
	bool keyState[NUM_OF_KEY_TYPE];

	//애니메이션 처리
	std::map<PartsType, CubeManParts*> animParts;
	void AnimationOnOff(bool on);

	bool GetCubeUVList(D3DXVECTOR2* out, PartsType type);

};

