#include "AlignedBoxCollider.h"



AlignedBoxCollider::AlignedBoxCollider()
{
}


AlignedBoxCollider::~AlignedBoxCollider()
{
}

DirectX::XMFLOAT3 AlignedBoxCollider::getExtends()
{
	return m_extends;
}

void AlignedBoxCollider::setExtends(DirectX::XMFLOAT3 vector)
{
	m_extends = vector;
}
