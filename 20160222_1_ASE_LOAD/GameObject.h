#pragma once

class GameObject
{
public:	
	GameObject(){};
	virtual ~GameObject(){};

	virtual void Destroy(){};
	virtual void Update(){};
	virtual void Render() = 0;

	inline const D3DXVECTOR3& GetPosition(){ return position; }
	inline D3DXVECTOR3* GetPositionAdress(){ return &position; }
	inline void SetPosition(const D3DXVECTOR3& pos){ position = pos; }
	inline void SetDirection(const D3DXVECTOR3& dir){ direction = dir; }
	inline void SetAngle(const float angle){ rotationAngle = angle; }

	
protected:
	D3DXVECTOR3	position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3	direction = D3DXVECTOR3(0, 0, 0);
	float rotationAngle = 0.0f;
	
};

