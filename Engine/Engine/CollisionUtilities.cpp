#include "CollisionUtilities.h"
#include "AlignedBoxCollider.h"
#include "SphereCollider.h"
#include "OrientedBoxCollider.h"
#include <DirectXCollision.h>
#include <Windows.h>
#include <string>

CollisionUtilities::CollisionUtilities()
{
}

CollisionUtilities::~CollisionUtilities()
{
}

bool CollisionUtilities::IntersectPointSphere(Collider * A, SphereCollider * B)
{
	Vector3 dot, sphere, distance;
	dot = A->getPosition();
	sphere = B->getPosition();
	distance = dot - sphere;
	if (distance.Magnitude() < B->getRadius())
	{
		return true;
	}

	return false;
}

bool CollisionUtilities::IntersectPointSphere(SphereCollider * A, Collider * B)
{
	return IntersectPointSphere(B,A);
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

	Vector3 yo = Vector3(2, 2, 2);
	yo = yo - Vector3(2, -2, 2);

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

bool CollisionUtilities::IntersectBoxSphere(SphereCollider * sphere, AlignedBoxCollider * box)
{
	return IntersectBoxSphere(box,sphere);
}

bool CollisionUtilities::IntersectAABB_OBB(AlignedBoxCollider * AABB, OrientedBoxCollider * obox)
{
	OrientedBoxCollider tmpcol;
	tmpcol.setExtends(AABB->getExtends());
	tmpcol.setPosition(AABB->getPosition());
	tmpcol.setRotation(DirectX::XMFLOAT3(0, 0, 0));

	return IntersectOrientedBoxes(&tmpcol,obox);
}

bool CollisionUtilities::IntersectAABB_OBB(OrientedBoxCollider * obox, AlignedBoxCollider * AABB)
{
	OrientedBoxCollider tmpcol;
	tmpcol.setExtends(AABB->getExtends());
	tmpcol.setPosition(AABB->getPosition());
	tmpcol.setRotation(DirectX::XMFLOAT3(0, 0, 0));


	return IntersectOrientedBoxes(&tmpcol, obox);
}

bool CollisionUtilities::IntersectOrientedBoxes(OrientedBoxCollider * obox1, OrientedBoxCollider * obox2)
{
	float rad = 0.0174533;

	DirectX::XMMATRIX rotation_matrix1 = DirectX::XMMatrixRotationRollPitchYaw(obox1->getRotation().x * rad,
																				obox1->getRotation().y * rad,
																				obox1->getRotation().z * rad);

	DirectX::XMMATRIX rotation_matrix2 = DirectX::XMMatrixRotationRollPitchYaw(obox2->getRotation().x * rad,
																				obox2->getRotation().y * rad,
																				obox2->getRotation().z * rad);

	Vector3 distance = Vector3(obox2->getPosition().x - obox1->getPosition().x,
													obox2->getPosition().y - obox1->getPosition().y, 
													obox2->getPosition().z - obox1->getPosition().z);


	float WA, HA, DA, WB, HB, DB;
	//WA - half width of box A
	//HA - half height of box A
	//so on...
	DirectX::XMFLOAT3 tmp = obox1->getExtends();
	WA = tmp.x;
	HA = tmp.y;
	DA = tmp.z;
	tmp = obox2->getExtends();
	WB = tmp.x;
	HB = tmp.y;
	DB = tmp.z;
	//pull the separating axis from rotation matrix
	//DirectX::XMFLOAT3 Ax, Ay, Az, Bx, By, Bz;

	Vector3 Ax, Ay, Az, Bx, By, Bz; 
	Vector3 cross_product;
	//if you are wondering why Vector3 and not XMFLOAT3, that is because i was tired of setting all individual components
	//of XMFLOAT3 when doing sum, subtract etc. operations
	//would implemet it into XMFLOAT3 but dammit the library would not let me save it
	//probably gonna replace XMFLOAT3 with Vector3 everywhere I can


	Ax = Vector3(DirectX::XMVectorGetX(rotation_matrix1.r[0]),
							DirectX::XMVectorGetY(rotation_matrix1.r[0]),
							DirectX::XMVectorGetZ(rotation_matrix1.r[0]));

	Ay = Vector3(DirectX::XMVectorGetX(rotation_matrix1.r[1]),
							DirectX::XMVectorGetY(rotation_matrix1.r[1]),
							DirectX::XMVectorGetZ(rotation_matrix1.r[1]));

	Az = Vector3(DirectX::XMVectorGetX(rotation_matrix1.r[2]),
							DirectX::XMVectorGetY(rotation_matrix1.r[2]),
							DirectX::XMVectorGetZ(rotation_matrix1.r[2]));

	Bx = Vector3(DirectX::XMVectorGetX(rotation_matrix2.r[0]),
							DirectX::XMVectorGetY(rotation_matrix2.r[0]),
							DirectX::XMVectorGetZ(rotation_matrix2.r[0]));

	By = Vector3(DirectX::XMVectorGetX(rotation_matrix2.r[1]),
							DirectX::XMVectorGetY(rotation_matrix2.r[1]),
							DirectX::XMVectorGetZ(rotation_matrix2.r[1]));

	Bz = Vector3(DirectX::XMVectorGetX(rotation_matrix2.r[2]),
							DirectX::XMVectorGetY(rotation_matrix2.r[2]),
							DirectX::XMVectorGetZ(rotation_matrix2.r[2]));

	//general inequality
	/*  | T • L | > | (WA*Ax) • L | +| (HA*Ay) • L | +| (DA*Az) • L | + | (WB*Bx) • L | +| (HB*By) • L | +| (DB*Bz) • L | */
	// T = distance
	//go trought all 15 possible separating axes
	//oh boy this ill take a lot of time

//CASE 1:
//	L = Ax

	if (!checkSeparatingAxes(distance, Ax, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

		
//	CASE 2 :
//L = Ay
	if (!checkSeparatingAxes(distance, Ay, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 3 :
//L = Az
	
	if (!checkSeparatingAxes(distance, Az, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 4 :
//L = Bx
	if (!checkSeparatingAxes(distance, Bx, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}


//	CASE 5 :
//	L = By
	if (!checkSeparatingAxes(distance, By, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//	CASE 6 :
//L = Bz
	if (!checkSeparatingAxes(distance, Bz, Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}


//	CASE 7 :
//	L = Ax x Bx
	if (!checkSeparatingAxes(distance, cross(Ax,Bx), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 8 :
//L = Ax x By
	if (!checkSeparatingAxes(distance, cross(Ax, By), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 9 :
//L = Ax x Bz
	if (!checkSeparatingAxes(distance, cross(Ax, Bz), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 10 :
//L = Ay x Bx
	if (!checkSeparatingAxes(distance, cross(Ay, Bx), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 11 :
//L = Ay x By
	if (!checkSeparatingAxes(distance, cross(Ay, By), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 12 :
//L = Ay x Bz
	if (!checkSeparatingAxes(distance, cross(Ay, Bz), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 13 :
//L = Az x Bx
	if (!checkSeparatingAxes(distance, cross(Az, Bx), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 14 :
//L = Az x By
	if (!checkSeparatingAxes(distance, cross(Az, By), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

//CASE 15 :
//L = Az x Bz
	if (!checkSeparatingAxes(distance, cross(Az, Bz), Ax, Ay, Az, Bx, By, Bz, WA, HA, DA, WB, HB, DB))
	{
		return false;
	}

	
	return true;
}

bool CollisionUtilities::IntersectOrientedBoxSphere(OrientedBoxCollider * obox, SphereCollider * sphere)
{
	float rad = 0.0174533;

	DirectX::XMMATRIX rotation_matrix = DirectX::XMMatrixRotationRollPitchYaw(obox->getRotation().x * rad,
		obox->getRotation().y * rad,
		obox->getRotation().z * rad);

	Vector3 distance = Vector3(obox->getPosition().x - sphere->getPosition().x,
		obox->getPosition().y - sphere->getPosition().y,
		obox->getPosition().z - sphere->getPosition().z);

	float dist_mag = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
	Vector3 distance_normalised;

	if (dist_mag != 0)
	{
		distance_normalised = distance / dist_mag;
	}
	else
	{
		//I mean...
		//if their positions are overlapping, you can always consider it as collision right?
		return true;

	}

	Vector3 sphere_vector_towards_center_of_cube = distance_normalised * sphere->getRadius();

	Vector3 Ax, Ay, Az;
	float WA, HA, DA;

	Ax = Vector3(DirectX::XMVectorGetX(rotation_matrix.r[0]),
		DirectX::XMVectorGetY(rotation_matrix.r[0]),
		DirectX::XMVectorGetZ(rotation_matrix.r[0]));

	Ay = Vector3(DirectX::XMVectorGetX(rotation_matrix.r[1]),
		DirectX::XMVectorGetY(rotation_matrix.r[1]),
		DirectX::XMVectorGetZ(rotation_matrix.r[1]));

	Az = Vector3(DirectX::XMVectorGetX(rotation_matrix.r[2]),
		DirectX::XMVectorGetY(rotation_matrix.r[2]),
		DirectX::XMVectorGetZ(rotation_matrix.r[2]));

	DirectX::XMFLOAT3 tmp = obox->getExtends();
	WA = tmp.x;
	HA = tmp.y;
	DA = tmp.z;

	//using the SAT find intersection
	//because we are checking a box against a simple vector, there are only 3 separating axes -> Ax, Ay, Az;
	//if dot product of 2 vectors equals 0 -> they are perpendicular, 
	//likewise if we know they are perpendicular we can instantly asume the value is 0
	//fabs(dot(Ax * WA, current_axis))
	
	if (fabs(dot(distance, Ax)) >= fabs(dot(Ax * WA, Ax)) +
									fabs(dot(Ay * HA, Ax)) +
									fabs(dot(Az * DA, Ax)) +
									fabs(dot(sphere_vector_towards_center_of_cube, Ax)))
	{
		
		
		return false;
	}

	

	if (fabs(dot(distance, Ay)) >= fabs(dot(Ax * WA, Ay)) +
									fabs(dot(Ay * HA, Ay)) +
									fabs(dot(Az * DA, Ay)) +
									fabs(dot(sphere_vector_towards_center_of_cube, Ay)))
	{
		
		
		return false;
	}

	
	if (fabs(dot(distance, Az)) >= fabs(dot(Ax * WA, Az)) +
									fabs(dot(Ay * HA, Az)) +
									fabs(dot(Az * HA, Az)) +
									fabs(dot(sphere_vector_towards_center_of_cube, Az)))
	{
		
		return false;
	}

	/*if (!fabs(dot(distance, Vector3(1,0,0)) >= fabs(dot(Ax * WA, Vector3(1, 0, 0))) +
												fabs(dot(Ay * HA, Vector3(1, 0, 0))) +
												fabs(dot(Az * DA, Vector3(1, 0, 0))) +
												fabs(dot(sphere_vector_towards_center_of_cube, Vector3(1, 0, 0)))))
	{
		OutputDebugStringA("X \n");
		return false;
	}

	if (!fabs(dot(distance, Vector3(0, 1, 0))) >= fabs(dot(Ax * WA, Vector3(0, 1, 0))) +
													fabs(dot(Ay * HA, Vector3(0, 1, 0))) +
													fabs(dot(Az * DA, Vector3(0, 1, 0))) +
													fabs(dot(sphere_vector_towards_center_of_cube, Vector3(0, 1, 0))))
	{
		OutputDebugStringA("Y \n");
		return false;
	}

	if (!fabs(dot(distance, Vector3(0, 0, 1))) >= fabs(dot(Ax * WA, Vector3(0, 0, 1))) +
													fabs(dot(Ay * HA, Vector3(0, 0, 1))) +
													fabs(dot(Az * DA, Vector3(0, 0, 1))) +
													fabs(dot(sphere_vector_towards_center_of_cube, Vector3(0, 0, 1))))
	{
		OutputDebugStringA("Z \n");
		return false;
	}*/

	
	return true;
}

bool CollisionUtilities::IntersectOrientedBoxSphere(SphereCollider * sphere, OrientedBoxCollider * obox)
{
	return IntersectOrientedBoxSphere(obox,sphere);
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

float CollisionUtilities::dot(Vector3 A, Vector3 B)
{
	return A.x*B.x + A.y*B.y + A.z*B.z;
}

DirectX::XMFLOAT3 CollisionUtilities::cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{

	return DirectX::XMFLOAT3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);
}

Vector3 CollisionUtilities::cross(Vector3 A, Vector3 B)
{
	return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);
}

float CollisionUtilities::absoluteValue(float f)
{
	float tmp = pow(f, 2);
	tmp = pow(tmp, 0.5);
	return tmp;
}

bool CollisionUtilities::intersectRange(float min0, float max0, float min1, float max1)
{
	return Max(min0, max0) >= Min(min1, max1) &&
		Min(min0, max0) <= Max(min1, max1);
}

bool CollisionUtilities::checkSeparatingAxes(Vector3 distance, Vector3 current_axis, Vector3 Ax, Vector3 Ay, Vector3 Az, Vector3 Bx, Vector3 By, Vector3 Bz, float WA, float HA, float DA, float WB, float HB, float DB)
{
	//return true if they are intersecting
	if (fabs(dot(distance, current_axis)) > fabs(dot(Ax * WA, current_axis)) +
											fabs(dot(Ay * HA, current_axis)) +
											fabs(dot(Az * DA, current_axis)) +
											fabs(dot(Bx * WB, current_axis)) +
											fabs(dot(By * HB, current_axis)) +
											fabs(dot(Bz * DB, current_axis)) )
	{
		
		return false;
	}

	return true;
}
