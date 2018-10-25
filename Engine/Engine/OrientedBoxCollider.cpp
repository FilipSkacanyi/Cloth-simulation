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

void OrientedBoxCollider::setRotation(DirectX::XMFLOAT3 rot)
{
	m_rotation = rot;
}
