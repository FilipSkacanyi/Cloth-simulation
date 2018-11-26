#pragma once


#include "GameObject.h"
class Cloth;

class ClothPoint : public GameObject
{
public:
	ClothPoint();
	~ClothPoint();
	void Init();
	void Tick(double dt) override;
	void setParent(Cloth* parent_) { m_parent = parent_; }
	void collision(GameObject* other) override;

	DirectX::XMFLOAT3 getPosition() override;

	
	
private:
	
	Cloth* m_parent = nullptr;

	
	
};

