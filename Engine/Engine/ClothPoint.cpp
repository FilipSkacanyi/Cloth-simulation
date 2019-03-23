#include "ClothPoint.h"
#include "Cloth.h"
#include "SphereCollider.h"
#include "Timer.h"

ClothPoint::ClothPoint()
{
	m_mass = 1;
	m_gravity = 1;
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
	/*m_position = DirectX::XMFLOAT3(m_parent->getPosition().x + m_object_position.x,
		m_parent->getPosition().y + m_object_position.y,
		m_parent->getPosition().z + m_object_position.z);*/

	

	//if (m_isKinematic)
	//{
	//	m_velocity = Vector3(0, 0, 0);
	//}
	//else
	//{
	//	//gravity
	//	AddForce(Vector3(0, -1, 0) * (m_mass*9.80) * dt * m_gravity);

	//	m_velocity = m_force;
	//	//velocity
	//	//m_position = DirectX::XMFLOAT3(m_position.x + dt * m_velocity.x, m_position.y + dt * 1 * m_velocity.y, m_position.z + dt * m_velocity.z);
	//	m_position = m_position + (m_velocity * dt);

	//	//AddForce(Vector3(-m_velocity.x * 0.9 * dt, -m_velocity.y * 0.9 * dt, -m_velocity.z * 0.9 * dt));
	//	AddForce(m_velocity * (-0.9) * dt);
	//}

	//m_collider->setPosition(m_position);


	Object::Tick(dt);
}

void ClothPoint::collision(GameObject * other)
{
	SphereCollider* temp =nullptr;
	temp = dynamic_cast<SphereCollider*> (other->getCollider());
	if (temp)
	{
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
		float distmag = distance.Magnitude() * 5;
		distance.Normalize();
		//this->AddForce(((velocity * (-0.1f) * m_mass) / Timer::Instance()->DeltaTime()));
		this->AddForce(distance * (-1));
	



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



