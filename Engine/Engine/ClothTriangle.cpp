#include "ClothTriangle.h"
#include "ClothPoint.h"
#include "TriangleCollider.h"
#include "Timer.h"



ClothTriangle::ClothTriangle()
{
	m_collider = new TriangleCollider();
	m_collider->Init(ColliderType::TRIANGLE);
}


ClothTriangle::~ClothTriangle()
{
}

void ClothTriangle::addPoints(ClothPoint * a, ClothPoint * b, ClothPoint * c)
{
	if (m_points.size() > 0)
	{
		m_points.clear();
	}

	m_points.push_back(a);
	m_points.push_back(b);
	m_points.push_back(c);
}

ClothPoint * ClothTriangle::getClothPointAtIndex(int i)
{
	return m_points[i];
}

void ClothTriangle::Tick(float dt)
{
	TriangleCollider* tmp = static_cast<TriangleCollider*>(m_collider);
	tmp->setPoints(m_points[0]->getPosition(), m_points[1]->getPosition(), m_points[2]->getPosition());
}

void ClothTriangle::AddForce(Vector3 force)
{
	for (int i = 0; i < m_points.size(); i++)
	{
		m_points[i]->AddForce(force);
	}
}

void ClothTriangle::collision(GameObject * other)
{
	ClothTriangle* tmp = static_cast<ClothTriangle*>(other);
	//tmp->AddForce();

	//force = mass * acceleration;
	//acceleration = force / mass

	//m_velocity = m_velocity + m_acceleration * dt;
	//velocity +(force /mass) *dt = 0
	//force *dt / mass = -velocity
	//force * dt = -velocity * mass
	//force = -velocity * mass / dt

	for (int i = 0; i < 3; i++)
	{
		ClothPoint* point = tmp->getClothPointAtIndex(i);
		Vector3 velocity = point->getVelocity();

		Vector3 distance = tmp->getPosition() - getPosition();
		float distmag = distance.Magnitude() * 5;
		distance.Normalize();
		point->AddForce(((velocity * (-0.1f) * point->getMass()) / Timer::Instance()->DeltaTime()));
		point->AddForce(distance * (0.1f / distmag));
	}


}

Vector3 ClothTriangle::getPosition()
{
	Vector3 averagePosition;
	  
	for (int i = 0; i < 3; i++)
	{
		averagePosition = averagePosition + m_points[i]->getPosition();
	}

	return averagePosition / 3;
}
