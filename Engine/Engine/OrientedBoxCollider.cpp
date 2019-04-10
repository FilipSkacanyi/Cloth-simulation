#include "OrientedBoxCollider.h"



OrientedBoxCollider::OrientedBoxCollider()
{
}


OrientedBoxCollider::~OrientedBoxCollider()
{
}

Vector3 OrientedBoxCollider::getRotation()
{
	return m_rotation;
}

void OrientedBoxCollider::setRotation(Vector3 rot)
{
	m_rotation = rot;
}
