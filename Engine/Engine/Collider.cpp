#include "Collider.h"
#include "OrientedBoxCollider.h"




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
	//sphere - sphere
	if(m_type == ColliderType::SPHERE && other->getType() == ColliderType::SPHERE)
	{
		SphereCollider* self = (SphereCollider*)(this);
		SphereCollider* tmpother = (SphereCollider*)(other);
		return CollisionUtilities::IntersectSpheres(self, tmpother);
	}

	//AABB - AABB
	if (m_type == ColliderType::AABB && other->getType() == ColliderType::AABB)
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectAlignedBoxes(self, otherbox);

	}

	//AABB - sphere
	if (m_type == ColliderType::AABB && other->getType() == ColliderType::SPHERE)
		
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		SphereCollider* tmpother = (SphereCollider*)(other);
		return CollisionUtilities::IntersectBoxSphere(self, tmpother);
	}
	//sphere - AABB
	if (m_type == ColliderType::SPHERE && other->getType() == ColliderType::AABB)
	{
		SphereCollider* self = (SphereCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectBoxSphere(self, otherbox);
	}
	//OBB - OBB
	if (m_type == ColliderType::ORIENTED && other->getType() == ColliderType::ORIENTED)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		OrientedBoxCollider* otherbox = (OrientedBoxCollider*)(other);
		return CollisionUtilities::IntersectOrientedBoxes(self, otherbox);
	}

	//OBB - AABB
	if (m_type == ColliderType::AABB && other->getType() == ColliderType::ORIENTED)
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		OrientedBoxCollider* otherbox = (OrientedBoxCollider*)(other);
			
		return CollisionUtilities::IntersectAABB_OBB(self, otherbox);
	}

	if(m_type == ColliderType::ORIENTED && other->getType() == ColliderType::AABB)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectAABB_OBB(self, otherbox);
	}
	
	//OBB - sphere
	if (m_type == ColliderType::ORIENTED && other->getType() == ColliderType::SPHERE)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		SphereCollider* tmpsphere = (SphereCollider*)(other);
		return CollisionUtilities::IntersectOrientedBoxSphere(self, tmpsphere);
	}
	if (m_type == ColliderType::SPHERE && other->getType() == ColliderType::ORIENTED)
	{
		OrientedBoxCollider* tmpsphere = (OrientedBoxCollider*)(other);
		SphereCollider* self = (SphereCollider*)(this);
		return CollisionUtilities::IntersectOrientedBoxSphere(self, tmpsphere);
	}

	return false;
}
