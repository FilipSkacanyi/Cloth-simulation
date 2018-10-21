#pragma once
#include "AlignedBoxCollider.h"


class OrientedBoxCollider :
	public AlignedBoxCollider
{
public:
	OrientedBoxCollider();
	~OrientedBoxCollider();

	DirectX::XMFLOAT3 getRotation();


private: 
	DirectX::XMFLOAT3 m_rotation;
};

