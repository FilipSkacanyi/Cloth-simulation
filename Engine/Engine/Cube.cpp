#include "Cube.h"
#include "AlignedBoxCollider.h"



Cube::Cube() : Object()
{
}


Cube::~Cube()
{
}

void Cube::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color)
{
	Object::Init(renderer, fileName, color);


	//create bounding box
	m_collider = new AlignedBoxCollider();

	AlignedBoxCollider* tmp = static_cast<AlignedBoxCollider*> (m_collider);
	tmp->Init(ColliderType::AABB);
	
	m_gravity = 1;
}

void Cube::Tick(double dt)
{
	Object::Tick(dt);

	/*SphereCollider* tmp = static_cast<SphereCollider*> (m_collider);
	tmp->setRadius(m_scale.x / 2);
	m_collider->setPosition(m_position);*/

	AlignedBoxCollider* tmp = static_cast<AlignedBoxCollider*> (m_collider);
	tmp->setPosition(m_position);
	tmp->setExtends(DirectX::XMFLOAT3(m_scale.x / 2, m_scale.y / 2, m_scale.z / 2));
}
