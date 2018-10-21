#include "OrientedBoxCollider.h"



OrientedBoxCollider::OrientedBoxCollider()
{
}


OrientedBoxCollider::~OrientedBoxCollider()
{
}

DirectX::XMFLOAT3 OrientedBoxCollider::getRotation()
{
	return m_rotation;
}
