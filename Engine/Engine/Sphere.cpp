#include "Sphere.h"
#include "SphereCollider.h"



Sphere::Sphere() : Object()
{
}


Sphere::~Sphere()
{
}

void Sphere::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color, std::wstring texturefile)
{
	Object::Init(renderer, fileName, color,texturefile);

	m_collider = new SphereCollider();
	m_collider->Init(ColliderType::SPHERE);
}

void Sphere::Tick(float dt)
{
	Object::Tick(dt);

	SphereCollider* tmp = static_cast<SphereCollider*> (m_collider);
	tmp->setRadius(m_scale.x * 1.1);
	m_collider->setPosition(m_position);
}
