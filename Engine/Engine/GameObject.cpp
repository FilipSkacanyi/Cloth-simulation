#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Tick(double dt)
{
	if (m_isKinematic)
	{
		m_velocity = Vector3(0, 0, 0);
	}
	else
	{
		//gravity
		AddForce(Vector3(0, -9.80 * m_mass, 0) * dt * m_gravity);
		//AddForce(m_acceleration * (-1) * (m_velocity.Magnitude() * m_velocity.Magnitude()));

		//force = mass * acceleration;
		//acceleration = force / mass
		m_acceleration = m_force / m_mass;

		//velocity
		m_velocity = m_velocity + m_acceleration * dt;
		//m_velocity = m_force;
		m_position = m_position + (m_velocity * dt);
		
		m_velocity = m_velocity - m_velocity * 0.95 *dt;
		 //air ressistance

		m_force = Vector3(0, 0, 0);

		
	}

	m_collider->setPosition(m_position);
}

Vector3 GameObject::getPosition()
{
	return m_position;
}

void GameObject::setPosition(Vector3 pos)
{
	m_position = pos;
}

void GameObject::AddForce(Vector3 force)
{
	m_force = m_force + force;
}


void GameObject::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setRotation(Vector3 rot)
{
	m_rotation = rot;
}

void GameObject::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setScale(Vector3 scale)
{
	m_scale = scale;
}

float GameObject::getMass()
{
	return m_mass;
}

void GameObject::setGravity(float grav)
{
	m_gravity = grav;
}

Collider * GameObject::getCollider()
{
	return m_collider;
}

Vector3 GameObject::getRotation()
{
	return m_rotation;
}

Vector3 GameObject::getScale()
{
	return m_scale;
}

void GameObject::collision(GameObject * other)
{
	//other->AddForce(Vector3(-m_velocity.x * (1  ), -m_velocity.y * (1 ), -m_velocity.z* (1 )/1000));
	Vector3 dir;
	dir = DirectX::XMFLOAT3((other->getPosition().x - m_position.x) ,( other->getPosition().y - m_position.y) , (other->getPosition().z - m_position.z) );
	//other->AddForce(dir / 10);
	
	//other->AddForce(m_velocity);

	//Vector3 normal = Vector3(m_position.x - other->getPosition().x, m_position.y - other->getPosition().y, m_position.z - other->getPosition().z);
	//normal.Normalize();
	//float mag = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y + m_velocity.z * m_velocity.z);

	////normal = normal * mag;
	//normal = normal * m_bounciness;

	//DirectX::XMFLOAT3 v = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
	//AddForce(v);
}