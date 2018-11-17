#pragma once


#include "GameObject.h"
class Cloth;

class ClothPoint : public GameObject
{
public:
	ClothPoint();
	~ClothPoint();

	void Tick(float dt) override;
	void setParent(Cloth* parent_) { m_parent = parent_; }
	

private:
	
	Cloth* m_parent = nullptr;

	
};

