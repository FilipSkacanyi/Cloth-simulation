#pragma once


#include "Renderer.h"
#include <string>
#include <fstream>
#include "Collider.h"
#include "GameObject.h"

enum VelocityAxis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	ALL_AXIS
};

class Object : public GameObject
{
public:
	Object();
	~Object();

	virtual void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color, std::wstring texturefile);
	void Tick(float dt) override;
	virtual void Render(Renderer* renderer);
	

	void AddForce(Vector3 force);

	float getMass();
	void setGravity(float grav);
	
	void setKinematic(bool b) { m_isKinematic = b; }
	bool isKinematic() { return m_isKinematic; }

	virtual void collision(GameObject* other) override;

	void resetVelocity(VelocityAxis axis);
	Vector3 getVelocity() { return m_velocity; }
	
protected:
	Model* m_model = nullptr;
	
	//physics stuff
	float m_bounciness = 0.33; 
	float m_mass = 1;
	Vector3 m_acceleration = Vector3(0, 0, 0);
	Vector3 m_velocity = Vector3(0, 0, 0);
	Vector3 m_force = Vector3(0, 0, 0);
	
	//air resistance
	float m_drag = 0.4f;
	float m_gravity = 1;

	//kinematic object cant be moved by forces
	bool m_isKinematic = false;
	

	float m_elapsed_time = 0;

		
};

