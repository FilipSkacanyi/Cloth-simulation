#pragma once

#include <DirectXMath.h>
#include "CollisionUtilities.h"
class Cloth;
class ClothPoint
{
public:
	ClothPoint();
	~ClothPoint();

	void Tick(float dt);
	DirectX::XMFLOAT3 getPosition();
	void setParent(Cloth* parent_) { m_parent = parent_; }
	void setPosition(DirectX::XMFLOAT3 pos);
	void AddForce(Vector3 force);

	void setKinematic(bool b) { m_isKinematic = b; }

private:
	DirectX::XMFLOAT3 m_position;
	Cloth* m_parent = nullptr;

	float mass = 1;
	float gravity = 1;
	bool m_isKinematic = false;
	Vector3 m_velocity = Vector3(0, 0, 0);
};

