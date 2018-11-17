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

	void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color);
	virtual void Tick(double dt);
	void Render(Renderer* renderer);
	

	void resetVelocity(VelocityAxis axis);
	
	void collision(Object* other);

	

	

	

	
	

	Collider* getCollider();

	

protected:
	Model* m_model = nullptr;

	
	

	//physics stuff
	float m_bounciness = 0.33; 

	float m_elapsed_time = 0;

	Collider* m_collider = nullptr;
	
};

