#pragma once
#include <list>
#include "FVF.h"
#include "Triangle.h"

class CubeManParts_Light 
{
public:
	CubeManParts_Light();
	~CubeManParts_Light();

	void Initialize(D3DXVECTOR3& cubeSize = D3DXVECTOR3(1, 1, 1), D3DXVECTOR3& pivot = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3& baseLocal = D3DXVECTOR3(0, 0, 0));
	void Destroy();
	void Render();
	void Update(D3DXMATRIX* parentWorldMatrix = nullptr);

	void SetTextureUV(D3DXVECTOR2* uvList);
	
	inline void AddChild(CubeManParts_Light* parts){ child.push_back(parts); }
	inline void SetRotation(float angle){ rotationAxisX = angle; }
	inline void SetRotationSpeed(float speed){ rotationSpeed = speed; stopReservation = false; }
	inline void StopRotationX(){ stopReservation = true; }
	
	inline void AttachLight(D3DLIGHT9* light, DWORD index, D3DXVECTOR3& lightLocal = D3DXVECTOR3(0, 0, 0)){ attachedLight = light; attachedLightIndex = index; attachedLightLocal = lightLocal; }


protected:

	static const int TRIANGLE_COUNT = 12;
	TextureNormalTriangle triangles[TRIANGLE_COUNT];
	
	D3DXMATRIXA16 world;
		
	float rotationAxisX = 0.0f;
	float rotationSpeed = 0.0f;
	D3DXVECTOR3 localTranslation = D3DXVECTOR3(0, 0, 0);

	std::list<CubeManParts_Light*> child;

	bool stopReservation = false;
		
	D3DLIGHT9* attachedLight = nullptr;
	DWORD attachedLightIndex = -1;
	D3DXVECTOR3 attachedLightLocal = D3DXVECTOR3(0, 0, 0);
};

