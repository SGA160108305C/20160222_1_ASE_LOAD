#pragma once
#include "ObjFileGroup.h"


class Obj
{
public:
	Obj();
	~Obj();

	void Initialize(char* mapFileName, char* groundFileName = nullptr);
	void Destroy();
	void Update();
	void Render();

	bool GroundCheck(IN OUT D3DXVECTOR3& groundPos) const;
	
	inline void SetPosition(D3DXVECTOR3& pos){ position = pos; }

private:
	
	D3DXMATRIX world;
	D3DXMATRIX rotation;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);

	std::vector<ObjFileGroup*> objGroups;
	std::vector<D3DXVECTOR3> objGround;
};

