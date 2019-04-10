

#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider();
	~SphereCollider();

	
	float getRadius();
	void setRadius(float rad);

private:

	float radius =1 ;
};
