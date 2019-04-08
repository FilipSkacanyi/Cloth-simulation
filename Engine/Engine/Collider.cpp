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

Vector3 Collider::getPosition()
{
	return m_position;
}

void Collider::setPosition(Vector3 pos)
{
	m_position = pos;
}

bool Collider::Intersect(Collider* other)
{
	ColliderType othertype = other->getType();

	//sphere - sphere
	if(m_type == ColliderType::SPHERE && othertype == ColliderType::SPHERE)
	{
		SphereCollider* self = (SphereCollider*)(this);
		SphereCollider* tmpother = (SphereCollider*)(other);
		return CollisionUtilities::IntersectSpheres(self, tmpother);
	}

	//AABB - AABB
	if (m_type == ColliderType::AABB && othertype == ColliderType::AABB)
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectAlignedBoxes(self, otherbox);

	}

	//AABB - sphere
	if (m_type == ColliderType::AABB && othertype == ColliderType::SPHERE)
		
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		SphereCollider* tmpother = (SphereCollider*)(other);
		return CollisionUtilities::IntersectBoxSphere(self, tmpother);
	}
	//sphere - AABB
	if (m_type == ColliderType::SPHERE && othertype == ColliderType::AABB)
	{
		SphereCollider* self = (SphereCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectBoxSphere(self, otherbox);
	}
	//OBB - OBB
	if (m_type == ColliderType::ORIENTED && othertype == ColliderType::ORIENTED)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		OrientedBoxCollider* otherbox = (OrientedBoxCollider*)(other);
		return CollisionUtilities::IntersectOrientedBoxes(self, otherbox);
	}

	//OBB - AABB
	if (m_type == ColliderType::AABB && othertype == ColliderType::ORIENTED)
	{
		AlignedBoxCollider* self = (AlignedBoxCollider*)(this);
		OrientedBoxCollider* otherbox = (OrientedBoxCollider*)(other);
			
		return CollisionUtilities::IntersectAABB_OBB(self, otherbox);
	}

	if(m_type == ColliderType::ORIENTED && othertype == ColliderType::AABB)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		AlignedBoxCollider* otherbox = (AlignedBoxCollider*)(other);
		return CollisionUtilities::IntersectAABB_OBB(self, otherbox);
	}
	
	//OBB - sphere
	if (m_type == ColliderType::ORIENTED && othertype == ColliderType::SPHERE)
	{
		OrientedBoxCollider* self = (OrientedBoxCollider*)(this);
		SphereCollider* tmpsphere = (SphereCollider*)(other);
		return CollisionUtilities::IntersectOrientedBoxSphere(self, tmpsphere);
	}
	
	if (m_type == ColliderType::SPHERE && othertype == ColliderType::ORIENTED)
	{
		OrientedBoxCollider* tmpsphere = (OrientedBoxCollider*)(other);
		SphereCollider* self = (SphereCollider*)(this);
		return CollisionUtilities::IntersectOrientedBoxSphere(self, tmpsphere);
	}

	if (m_type == ColliderType::SINGLE_POINT && othertype == ColliderType::SPHERE)
	{
		SphereCollider* tmpsphere = (SphereCollider*)(other);
		return CollisionUtilities::IntersectPointSphere(this, tmpsphere);
	}

	if (m_type == ColliderType::SPHERE && othertype == ColliderType::SINGLE_POINT)
	{
		SphereCollider* self = (SphereCollider*)(other);
		return CollisionUtilities::IntersectPointSphere(other, self);
	}

	if (m_type == ColliderType::TRIANGLE && othertype == ColliderType::TRIANGLE)
	{
		TriangleCollider* other_ = (TriangleCollider*)(other);
		TriangleCollider* self_ = (TriangleCollider*)(this);

		return CollisionUtilities::IntersectTriangles(other_,self_);
	}

	return false;
}
