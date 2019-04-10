#pragma once


#include "Object.h"
class Cloth;

class ClothPoint : public Object
{
public:
	ClothPoint();
	~ClothPoint();
	void Init();
	void Tick(float dt) override;
	void setParent(Cloth* parent_) { m_parent = parent_; }
	void collision(GameObject* other) override;

	Vector3 getPosition() override;

	Vector3 getVelocity() { return m_velocity; }
	DirectX::XMFLOAT4 getColor() { return m_color; }
	void setColor(float r, float g, float b);
private:
		
	Cloth* m_parent = nullptr;
	DirectX::XMFLOAT4 m_color = DirectX::XMFLOAT4(1, 0, 0, 1);
	
};

