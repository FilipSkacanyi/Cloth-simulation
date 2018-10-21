#include "CollisionUtilities.h"
#include "AlignedBoxCollider.h"
#include "SphereCollider.h"
#include "OrientedBoxCollider.h"
#include <DirectXCollision.h>

CollisionUtilities::CollisionUtilities()
{
}

CollisionUtilities::~CollisionUtilities()
{
}

bool CollisionUtilities::IntersectAlignedBoxes(AlignedBoxCollider * A, AlignedBoxCollider * B)
{
	if (intersectRange(A->getPosition().x - A->getExtends().x, A->getPosition().x + A->getExtends().x, B->getPosition().x - B->getExtends().x, B->getPosition().x + B->getExtends().x) &&
		intersectRange(A->getPosition().y - A->getExtends().y, A->getPosition().y + A->getExtends().y, B->getPosition().y - B->getExtends().y, B->getPosition().y + B->getExtends().y) &&
		intersectRange(A->getPosition().z - A->getExtends().z, A->getPosition().z + A->getExtends().z, B->getPosition().z - B->getExtends().z, B->getPosition().z + B->getExtends().z)
		)
	{
		return true;
	}

	return false;

}

bool CollisionUtilities::IntersectSpheres(SphereCollider * A, SphereCollider * B)
{
	float x, y, z, distance, magnitude;

	//subtract positions to get a vector betwwen the to objects
	x = A->getPosition().x - B->getPosition().x;
	y = A->getPosition().y - B->getPosition().y;
	z = A->getPosition().z - B->getPosition().z;

	distance = A->getRadius() + B->getRadius();

	//
	magnitude = pow((pow(x, 2) + pow(y, 2) + pow(z, 2)), 0.5);

	if (magnitude < distance)
	{
		return true;
	}
	return false;
}

bool CollisionUtilities::IntersectBoxSphere(AlignedBoxCollider * box, SphereCollider * sphere)
{
	//find closest point
	DirectX::XMFLOAT3 closestPoint = DirectX::XMFLOAT3(0, 0, 0);

	//x coord
	if (sphere->getPosition().x < box->getPosition().x - box->getExtends().x)
	{
		closestPoint.x = box->getPosition().x - box->getExtends().x;
	}
	else if (sphere->getPosition().x > box->getPosition().x + box->getExtends().x)
	{
		closestPoint.x = box->getPosition().x + box->getExtends().x;
	}
	else
	{
		closestPoint.x = sphere->getPosition().x;
	}
	//y coord
	if (sphere->getPosition().y < box->getPosition().y - box->getExtends().y)
	{
		closestPoint.y = box->getPosition().y - box->getExtends().y;
	}
	else if (sphere->getPosition().y > box->getPosition().y + box->getExtends().y)
	{
		closestPoint.y = box->getPosition().y + box->getExtends().y;
	}
	else
	{
		closestPoint.y = sphere->getPosition().y;
	}
	//z coord
	if (sphere->getPosition().z < box->getPosition().z - box->getExtends().z)
	{
		closestPoint.z = box->getPosition().z - box->getExtends().z;
	}
	else if (sphere->getPosition().z > box->getPosition().z + box->getExtends().z)
	{
		closestPoint.z = box->getPosition().z + box->getExtends().z;
	}
	else
	{
		closestPoint.z = sphere->getPosition().z;
	}

	//calculate distance between sphere and closest point
	float x, y, z, magnitude;
	x = sphere->getPosition().x - closestPoint.x;
	y = sphere->getPosition().y - closestPoint.y;
	z = sphere->getPosition().z - closestPoint.z;

	magnitude = pow((pow(x, 2) + pow(y, 2) + pow(z, 2)), 0.5);

	if (magnitude < sphere->getRadius())
	{
		return true;
	}
	return false;



}


float CollisionUtilities::Min(float f1, float f2)
{
	if (f1 > f2)
	{
		return f2;
	}
	else
	{
		return f1;
	}
}

float CollisionUtilities::Max(float f1, float f2)
{
	if (f1 < f2)
	{
		return f2;
	}
	else
	{
		return f1;
	}
}

float CollisionUtilities::dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
	return A.x*B.x + A.y*B.y + A.z*B.z;
}

bool CollisionUtilities::intersectRange(float min0, float max0, float min1, float max1)
{
	return Max(min0, max0) >= Min(min1, max1) &&
		Min(min0, max0) <= Max(min1, max1);
}
