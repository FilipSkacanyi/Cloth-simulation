#include "Cube.h"
#include "OrientedBoxCollider.h"



Cube::Cube() : Object()
{
}


Cube::~Cube()
{
}

void Cube::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color, std::wstring texturefile)
{
	Object::Init(renderer, fileName, color,texturefile);


	//create bounding box
	m_collider = new OrientedBoxCollider();

	OrientedBoxCollider * tmp = (OrientedBoxCollider*)(m_collider);
	tmp->Init(ColliderType::ORIENTED);
	
	m_gravity = 1;

	m_mass = 20;
}

void Cube::Tick(float dt)
{
	Object::Tick(dt);

	/*SphereCollider* tmp = static_cast<SphereCollider*> (m_collider);
	tmp->setRadius(m_scale.x / 2);
	m_collider->setPosition(m_position);*/

	OrientedBoxCollider* tmp = static_cast<OrientedBoxCollider*> (m_collider);
	tmp->setPosition(m_position);
	tmp->setRotation(m_rotation);
	tmp->setExtends(DirectX::XMFLOAT3(m_scale.x / 2, m_scale.y / 2, m_scale.z / 2));
}
