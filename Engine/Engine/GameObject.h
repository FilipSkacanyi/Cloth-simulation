#pragma once

#include <DirectXMath.h>
#include "CollisionUtilities.h"
#include "Collider.h"

class Grid;
struct Cell;
class GameObject
{
public:
	GameObject();
	~GameObject();


	virtual void Tick(double dt);
	virtual Vector3 getPosition();
	Vector3 getRotation();
	Vector3 getScale();

	void setPosition(Vector3 pos);

	void setRotation(float x, float y, float z);
	void setRotation(Vector3 rot);
	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);

	void AddForce(Vector3 force);

	float getMass();
	void setGravity(float grav);
	Collider* getCollider(); 
	void setKinematic(bool b) { m_isKinematic = b; }
	bool isKinematic() { return m_isKinematic; }

	virtual void collision(GameObject* other);


protected:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;

	float m_mass = 1;
	Vector3 m_acceleration = Vector3(0, 0, 0);
	Vector3 m_velocity = Vector3(0, 0, 0);
	Vector3 m_force = Vector3(0, 0, 0);

	float m_gravity = 1;
	bool m_isKinematic = false;
	Collider* m_collider = nullptr;


	
};

