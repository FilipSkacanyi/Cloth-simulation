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
	
private:
		
	Cloth* m_parent = nullptr;
		
	
};

