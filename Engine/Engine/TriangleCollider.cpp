#include "TriangleCollider.h"



TriangleCollider::TriangleCollider()
{
}


TriangleCollider::~TriangleCollider()
{
}

void TriangleCollider::setPoints(Vector3 a, Vector3 b, Vector3 c)
{
	m_points[0] = a;
	m_points[1] = b;
	m_points[2] = c;
}

Vector3 TriangleCollider::getPointAtIndex(int i)
{

	return m_points[i];
}
