#include "Sphere.h"
#include "SphereCollider.h"



Sphere::Sphere() : Object()
{
}


Sphere::~Sphere()
{
}

void Sphere::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color)
{
	Object::Init(renderer, fileName, color);

	m_collider = new SphereCollider();
	m_collider->Init(ColliderType::SPHERE);
}

void Sphere::Tick(double dt)
{
	Object::Tick(dt);

	SphereCollider* tmp = static_cast<SphereCollider*> (m_collider);
	tmp->setRadius(m_scale.x / 2);
	m_collider->setPosition(m_position);
}
