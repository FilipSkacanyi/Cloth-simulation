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
	Vector3 distance;
	Vector3 posA;
	Vector3 posB;
	Vector3 force;
	

	posA = m_point_A->getPosition();
	posB = m_point_B->getPosition();

	distance = posA - posB;

	
	if (m_type == SpringType::STRAIT)
	{
		float distmag = 0;
		distmag = distance.Magnitude();
		distmag = distmag - m_offset_distance;
		distance.Normalize();
		distance = distance * distmag;
		//offset = offset * m_offset_distance;
	}
	else if (m_type == SpringType::DIAGONAL)
	{
		float distmag = 0;
		distmag = distance.Magnitude();
		distmag = distmag - m_offset_distance * sqrt(2);
		distance.Normalize();
		distance = distance * distmag;
		//offset = offset * m_offset_distance * sqrt(2);
	}

	force = distance *m_stiffness;
	//force = distance ;
	m_point_A->AddForce(force*(-1)  );
	m_point_B->AddForce(force  );
	
	

}

void Spring::assignPoints(ClothPoint * pointA, ClothPoint * pointB, float offset_distance)
{
	m_point_A = pointA;
	m_point_B = pointB;
	m_offset_distance = offset_distance;
}
