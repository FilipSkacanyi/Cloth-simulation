

#pragma once
#include "Collider.h"

class AlignedBoxCollider :
	public Collider
{
public:
	AlignedBoxCollider();
	~AlignedBoxCollider();

	DirectX::XMFLOAT3 getExtends();

private:
	DirectX::XMFLOAT3 m_extends;
};

