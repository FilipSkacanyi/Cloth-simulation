#include "ClothTriangle.h"
#include "ClothPoint.h"



ClothTriangle::ClothTriangle()
{
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

void ClothTriangle::AddForce(Vector3 force)
{
	for (int i = 0; i < m_points.size(); i++)
	{
		m_points[i]->AddForce(force);
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
