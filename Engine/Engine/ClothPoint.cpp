#include "ClothPoint.h"
#include "Cloth.h"
#include "SphereCollider.h"
#include "Sphere.h"
#include "Timer.h"


ClothPoint::ClothPoint()
{
	m_mass = 1;
	m_gravity = 1;
	m_drag = 0.0f;
}


ClothPoint::~ClothPoint()
{
}

void ClothPoint::Init()
{
	m_collider = new Collider();
	m_collider->Init(ColliderType::SINGLE_POINT);
}

void ClothPoint::Tick(float dt)
{
	m_color = DirectX::XMFLOAT4(1, 0, 0, 1);


	Object::Tick(dt);
}

void ClothPoint::collision(GameObject * other)
{
	SphereCollider* temp = nullptr;
	temp = dynamic_cast<SphereCollider*> (other->getCollider());
	if (temp)
	{
		Sphere*  sphere = static_cast<Sphere*>(other);

		Vector3 pos;
		Vector3 other_pos;

		pos = m_position;
		other_pos = other->getPosition();

		Vector3 distance;
		distance = pos - other_pos;

		float radius = temp->getRadius();

		distance.Normalize();
		distance = distance * radius;

		m_position = DirectX::XMFLOAT3(other_pos.x + distance.x, other_pos.y + distance.y, other_pos.z + distance.z);


		Vector3 velocity = m_velocity;
		distance = temp->getPosition() - m_position;
		float distmag = distance.Magnitude() * 10;
		distance.Normalize();


		//apply a bit of force so the points do not get stuck on the surface
		this->AddForce(distance * (-2));
		distance = distance * distmag;
		//slow the sphere down as a result of collision
		sphere->AddForce(distance * sphere->getVelocity().Magnitude() * Timer::Instance()->DeltaTime() );


	}
	else
	{
		OutputDebugString("Collidion detected but not with a sphere\n");
	}
}

Vector3 ClothPoint::getPosition()
{
	return m_position;
}

void ClothPoint::setColor(float r, float g, float b)
{
	m_color = DirectX::XMFLOAT4(r, g, b, 1);
}



