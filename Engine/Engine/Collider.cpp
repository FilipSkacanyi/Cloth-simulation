#include "Collider.h"




Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::Init(ColliderType type)
{
	m_type = type;
}

ColliderType Collider::getType()
{
	return m_type;
}

DirectX::XMFLOAT3 Collider::getPosition()
{
	return m_position;
}

void Collider::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}

bool Collider::Intersect(Collider* other)
{
	if(m_type == ColliderType::SPHERE && other->getType() == ColliderType::SPHERE)
	{
		SphereCollider* self = (SphereCollider*)(this);
		SphereCollider* tmpother = (SphereCollider*)(other);
		return CollisionUtilities::IntersectSpheres(self, tmpother);
	}

	if (m_type == ColliderType::AABB && other->getType() == ColliderType::AABB)
	{
		//AlignedBoxCollider* self = static_cast<AlignedBoxCollider*>(this);
		//AlignedBoxCollider* otherBox = static_cast<AlignedBoxCollider*>(other);
		//IntersectAlignedBoxes(self, otherBox);

	}

	if (m_type == ColliderType::AABB && other->getType() == ColliderType::SPHERE)
	{
		//AlignedBoxCollider* self = static_cast<AlignedBoxCollider*>(this);
		//SphereCollider* otherSphere = static_cast<SphereCollider*>(other);
		//IntersectBoxSphere(otherSphere, self);
	}

	if (m_type == ColliderType::SPHERE && other->getType() == ColliderType::AABB)
	{
		//SphereCollider* self = static_cast<SphereCollider*>(this);
		//AlignedBoxCollider* otherBox = static_cast<AlignedBoxCollider*>(other);
		//IntersectBoxSphere(self, other);
	}
	
	return false;
}
