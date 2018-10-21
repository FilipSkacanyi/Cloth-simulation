#pragma once


#include "Renderer.h"
#include <string>
#include <fstream>
#include "Collider.h"

enum VelocityAxis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	ALL_AXIS
};

class Object
{
public:
	Object();
	~Object();

	void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color);
	virtual void Tick(double dt);
	void Render(Renderer* renderer);

	void setPosition(float x, float y, float z);
	void setPosition(DirectX::XMFLOAT3 pos);
	void setRotation(float x, float y, float z);
	void setRotation(DirectX::XMFLOAT3 rot);
	void setScale(float x, float y, float z);
	void setScale(DirectX::XMFLOAT3 scale);

	void resetVelocity(VelocityAxis axis);
	void AddForce(DirectX::XMFLOAT3 force);
	void collision(Object* other);

	float getMass();

	void setGravity(float grav);


	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();

	Collider* getCollider();

	

protected:
	Model* m_model = nullptr;

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;

	//physics stuff
	float m_mass = 1;
	DirectX::XMFLOAT3 m_velocity = DirectX::XMFLOAT3(0,0,0);
	float m_gravity = 1;

	float m_elapsed_time = 0;

	Collider* m_collider = nullptr;
	
};

