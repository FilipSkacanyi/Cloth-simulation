#pragma once

#include <DirectXMath.h>
#include "CollisionUtilities.h"

class GameObject
{
public:
	GameObject();
	~GameObject();


	virtual void Tick(float dt);
	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();

	void setPosition(DirectX::XMFLOAT3 pos);

	void setRotation(float x, float y, float z);
	void setRotation(DirectX::XMFLOAT3 rot);
	void setScale(float x, float y, float z);
	void setScale(DirectX::XMFLOAT3 scale);

	void AddForce(Vector3 force);

	float getMass();
	void setGravity(float grav);

	void setKinematic(bool b) { m_isKinematic = b; }
protected:
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;

	float m_mass = 1;
	float m_gravity = 1;
	bool m_isKinematic = false;
	Vector3 m_velocity = Vector3(0, 0, 0);
};

