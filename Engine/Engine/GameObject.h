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

	Collider* getCollider();

	virtual void collision(GameObject* other);

protected:
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;

	Collider* m_collider = nullptr;
	
};

