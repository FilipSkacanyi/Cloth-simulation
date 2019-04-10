
#pragma once

#include "CollisionUtilities.h"

enum ColliderType
{
	SPHERE,
	AABB,
	ORIENTED,
	SINGLE_POINT,
	TRIANGLE
};

class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual void Init(ColliderType type);

	ColliderType getType();
	Vector3 getPosition();
	void setPosition(Vector3 pos);

	 bool Intersect(Collider* other);

protected:

	Vector3 m_position;
	ColliderType m_type;

};

