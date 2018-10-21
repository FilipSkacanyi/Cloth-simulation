
#pragma once

#include "CollisionUtilities.h"

enum ColliderType
{
	SPHERE,
	AABB,
	ORIENTATED
};

class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual void Init(ColliderType type);

	ColliderType getType();
	DirectX::XMFLOAT3 getPosition();
	void setPosition(DirectX::XMFLOAT3 pos);

	 bool Intersect(Collider* other);

protected:

	DirectX::XMFLOAT3 m_position;
	ColliderType m_type;

};

