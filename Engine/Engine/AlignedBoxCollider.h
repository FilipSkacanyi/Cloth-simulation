

#pragma once
#include "Collider.h"

class AlignedBoxCollider :
	public Collider
{
public:
	AlignedBoxCollider();
	~AlignedBoxCollider();

	DirectX::XMFLOAT3 getExtends();
	void setExtends(DirectX::XMFLOAT3 vector);

protected:
	DirectX::XMFLOAT3 m_extends;
};

