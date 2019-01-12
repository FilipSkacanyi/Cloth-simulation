#pragma once
#include "AlignedBoxCollider.h"


class OrientedBoxCollider :
	public AlignedBoxCollider
{
public:
	OrientedBoxCollider();
	~OrientedBoxCollider();

	Vector3 getRotation();

	void setRotation(Vector3 rot);

private: 
	Vector3 m_rotation;
};

