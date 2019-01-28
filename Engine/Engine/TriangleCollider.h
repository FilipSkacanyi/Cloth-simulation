#pragma once
#include "Collider.h"


class TriangleCollider :
	public Collider
{
public:
	TriangleCollider();
	~TriangleCollider();

	void setPoints(Vector3 a, Vector3 b, Vector3 c);
	Vector3 getPointAtIndex(int i);

private:

	Vector3 m_points[3];
};

