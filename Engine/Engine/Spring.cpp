#include "Spring.h"
#include "ClothPoint.h"
#include "CollisionUtilities.h"


Spring::Spring()
{
}


Spring::~Spring()
{
}

void Spring::Tick(float dt)
{
	Vector3 direction;
	Vector3 posA;
	Vector3 posB;
	Vector3 distance;
	

	posA = m_point_A->getPosition();
	posB = m_point_B->getPosition();

	direction = posB - posA;

	float offset = 0;
	if (m_type == SpringType::STRAIT)
	{
		offset = m_offset_distance;
		//offset = offset * m_offset_distance;
	}
	else if (m_type == SpringType::DIAGONAL)
	{
		offset = m_offset_distance * sqrt(2);
		//offset = offset * m_offset_distance * sqrt(2);
	}

	float current_length = direction.Magnitude();
	direction.Normalize();
	float stretch = current_length - offset;
	direction = direction *(-m_stiffness * stretch);
	
	m_point_A->AddForce(direction * (-1000) * dt);
	m_point_B->AddForce(direction * (1000) * dt);

	distance = posB - posA;

	if (distance.Magnitude() > offset * m_max_stretch)
	{
		if (!(m_point_A->isKinematic() && m_point_B->isKinematic()))
		{

			if (m_point_A->isKinematic())
			{
				//bring pointB closer
				distance.Normalize();
				distance = distance * offset  * m_max_stretch;

				Vector3 newpos;
				newpos = m_point_A->getPosition();
				newpos = newpos + distance;

				m_point_B->setPosition(newpos);
				//m_point_B->setPosition()
			}
			else if (m_point_B->isKinematic())
			{
				//bring pointA closer
				distance = distance * (-1);
				distance.Normalize();
				distance = distance * offset  * m_max_stretch;

				m_point_A->setPosition(m_point_B->getPosition() + distance);
			}
			else
			{
				//bring both closer equally
				Vector3 currentdist = distance;
				
				distance.Normalize();
				distance = distance * offset  * m_max_stretch;

				Vector3 difference;
				difference = currentdist - distance;
				difference = difference / 2;

				m_point_A->setPosition(m_point_A->getPosition() + difference);

				m_point_B->setPosition(m_point_B->getPosition() - difference);
			}
		}

	}
		
	
}

void Spring::assignPoints(Object * pointA, Object * pointB, float offset_distance)
{
	m_point_A = pointA;
	m_point_B = pointB;
	m_offset_distance = offset_distance;
}
