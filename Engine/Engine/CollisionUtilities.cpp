#include "CollisionUtilities.h"
#include "AlignedBoxCollider.h"
#include "SphereCollider.h"
#include "OrientedBoxCollider.h"
#include <DirectXCollision.h>
#include <Windows.h>
#include <string>
#include "Triangle.h"
#include "ClothTriangle.h"
#include "ClothPoint.h"
#include "TriangleCollider.h"

#include "trianglecol.h"
#include "Tricol2.h"

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
	float radius_sum = A->getRadius() + B->getRadius();

	Vector3 distance;
	distance = A->getPosition() - B->getPosition();

	if (distance.Magnitude() < radius_sum)
	{
		return true;
	}
	return false;
}

bool CollisionUtilities::IntersectBoxSphere(AlignedBoxCollider * box, SphereCollider * sphere)
{
	//find closest point
	Vector3 closestPoint = Vector3(0, 0, 0);

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
	Vector3 distance;
	distance = sphere->getPosition() - closestPoint;

	if (distance.Magnitude() < sphere->getRadius())
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
	tmpcol.setRotation(Vector3(0, 0, 0));

	return IntersectOrientedBoxes(&tmpcol,obox);
}

bool CollisionUtilities::IntersectAABB_OBB(OrientedBoxCollider * obox, AlignedBoxCollider * AABB)
{
	OrientedBoxCollider tmpcol;
	tmpcol.setExtends(AABB->getExtends());
	tmpcol.setPosition(AABB->getPosition());
	tmpcol.setRotation(Vector3(0, 0, 0));


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

	Vector3 distance = obox->getPosition() - sphere->getPosition();

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

bool CollisionUtilities::IntersectTriangles(Triangle * A, Triangle * B)
{
	Vector3 N1, N2;
	float d1, d2;
	float distances1[3], distances2[3];
	Vector3 posA = A->getPosition();
	Vector3 posB = B->getPosition();
	
	
	Vector3 t1_points[3];
	Vector3 t2_points[3];
	
	for (int i = 0; i < 3; i++)
	{
		t1_points[i] = A->getPoints()[i] + posA;
	t2_points[i] = B->getPoints()[i] + posB;
	}

	
	N2 = cross(t2_points[1] - t2_points[0], t2_points[2] - t2_points[0]);
	d2 = -1 * dot(N2, t2_points[0]);

	//calculate distances of vertices of one triangle from a plane of second triangle 
	for (int i = 0; i < 3; i++)
	{
		distances1[i] = dot(N2, t1_points[i]) + d2;
	}

	//if all have the same sign, there is noc collision
	if (distances1[0] > 0 && distances1[1] > 0 && distances1[2] > 0)
	{
		return false;
	}
	else if (distances1[0] < 0 && distances1[1] < 0 && distances1[2] < 0)
	{
		return false;
	}
	//if the distance is 0 that means the point is on the plane directly
	//meaning they probably share a point or an edge.
	//so far I am going to disregard it as well
	else if (distances1[0] == 0 || distances1[1] == 0 || distances1[2] == 0)
	{
		return false;
	}

	//same teste are done for other triangle... 
	//not sure if the second one is necessery
	
	N1 = cross(t1_points[1] - t1_points[0], t1_points[2] - t1_points[0]);
	d1 = -1 * dot(N1, t1_points[0]);

	for (int i = 0; i < 3; i++)
	{
		distances2[i] = dot(N1, t2_points[i]) + d1;
	}

	if (distances2[0] > 0 && distances2[1] > 0 && distances2[2] > 0)
	{
		return false;
	}
	else if (distances2[0] < 0 && distances2[1] < 0 && distances2[2] < 0)
	{
		return false;
	}
	else if (distances2[0] == 0 || distances2[1] == 0 || distances2[2] == 0)
	{
		return false;
	}

	//the intersection of planes is a line
	// line = a point on it + cross of N1xN2
	Vector3 D;
	D = cross(N1, N2);

	Vector3 T1_p, T2_p;

	T1_p.x = dot(D, t1_points[0]);
	T1_p.y = dot(D, t1_points[1]);
	T1_p.z = dot(D, t1_points[2]);

	T2_p.x = dot(D, t2_points[0]);
	T2_p.y = dot(D, t2_points[1]);
	T2_p.z = dot(D, t2_points[2]);

	float T1t1, T1t2, T2t1, T2t2;

	computeTriangleIntersectionIntervals(T1_p, distances1, T1t1, T1t2);
	computeTriangleIntersectionIntervals(T2_p, distances2, T2t1, T2t2);

	//sort the intervals so that the smaller number is on the left
	float tmp = 0;
	if (T1t1 > T1t2)
	{
		tmp = T1t1;
		T1t1 = T1t2;
		T1t2 = tmp;
		tmp = 0;
	}

	if (T2t1 > T2t2)
	{
		tmp = T2t1;
		T2t1 = T2t2;
		T2t2 = tmp;
	}

	if (T1t2 < T2t1 || T2t2 < T1t1)
	{
		
		return false;
	}
	
	return true;


 //   Vector3 posA = A->getPosition();
	//Vector3 posB = B->getPosition();

	//Vector3 t1_points[3];
	//Vector3 t2_points[3];
	//
	//double v1[3], v2[3], v3[3], u1[3], u2[3], u3[3], source[3], target[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	t1_points[i] = A->getPoints()[i] + posA;
	//	t2_points[i] = B->getPoints()[i] + posB;
	//}

	//Vector3tofloatArray(v1, t1_points[0]);
	//Vector3tofloatArray(v2, t1_points[1]);
	//Vector3tofloatArray(v3, t1_points[2]);
	//Vector3tofloatArray(u1, t2_points[0]);
	//Vector3tofloatArray(u2, t2_points[1]);
	//Vector3tofloatArray(u3, t2_points[2]);

	//int* coplanar = nullptr;
	//if (tri_tri_overlap_test_3d(v1, v2, v3, u1, u2, u3) == 0)
	//{
	//	return false;
	//}

	//	/*if (NoDivTriTriIsect(v1, v2, v3, u1, u2, u3) == 0)
	//	{
	//		return false;
	//	}
	//	else
	//	{
	//		return true;
	//	}*/
	//	return true;
}

bool CollisionUtilities::IntersectTriangles(ClothTriangle * A, ClothTriangle * B)
{
	Vector3 N1, N2;
	float d1, d2;
	float distances1[3], distances2[3];

	Vector3 t1_points[3];
	Vector3 t2_points[3];

	for (int i = 0; i < 3; i++)
	{
		t1_points[i] = A->getClothPointAtIndex(i)->getPosition();
		t2_points[i] = B->getClothPointAtIndex(i)->getPosition();
	}


	N2 = cross(t2_points[1] - t2_points[0], t2_points[2] - t2_points[0]);
	d2 = -1 * dot(N2, t2_points[0]);

	//calculate distances of vertices of one triangle from a plane of second triangle 
	for (int i = 0; i < 3; i++)
	{
		distances1[i] = dot(N2, t1_points[i]) + d2;
	}

	//if all have the same sign, there is noc collision
	if (distances1[0] > 0 && distances1[1] > 0 && distances1[2] > 0)
	{
		return false;
	}
	else if (distances1[0] < 0 && distances1[1] < 0 && distances1[2] < 0)
	{
		return false;
	}
	//if the distance is 0 that means the point is on the plane directly
	//meaning they probably share a point or an edge.
	//so far I am going to disregard it as well
	else if (distances1[0] == 0 || distances1[1] == 0 || distances1[2] == 0)
	{
		return false;
	}

	//same teste are done for other triangle... 
	//not sure if the second one is necessery

	N1 = cross(t1_points[1] - t1_points[0], t1_points[2] - t1_points[0]);
	d1 = -1 * dot(N1, t1_points[0]);

	for (int i = 0; i < 3; i++)
	{
		distances2[i] = dot(N1, t2_points[i]) + d1;
	}

	if (distances2[0] > 0 && distances2[1] > 0 && distances2[2] > 0)
	{
		return false;
	}
	else if (distances2[0] < 0 && distances2[1] < 0 && distances2[2] < 0)
	{
		return false;
	}
	else if (distances2[0] == 0 || distances2[1] == 0 || distances2[2] == 0)
	{
		return false;
	}

	//the intersection of planes is a line
	// line = a point on it + cross of N1xN2
	Vector3 D;
	D = cross(N1, N2);

	Vector3 T1_p, T2_p;

	T1_p.x = dot(D, t1_points[0]);
	T1_p.y = dot(D, t1_points[1]);
	T1_p.z = dot(D, t1_points[2]);

	T2_p.x = dot(D, t2_points[0]);
	T2_p.y = dot(D, t2_points[1]);
	T2_p.z = dot(D, t2_points[2]);

	float T1t1, T1t2, T2t1, T2t2;

	computeTriangleIntersectionIntervals(T1_p, distances1, T1t1, T1t2);
	computeTriangleIntersectionIntervals(T2_p, distances2, T2t1, T2t2);

	//sort the intervals so that the smaller number is on the left
	float tmp = 0;
	if (T1t1 > T1t2)
	{
		tmp = T1t1;
		T1t1 = T1t2;
		T1t2 = tmp;
		tmp = 0;
	}

	if (T2t1 > T2t2)
	{
		tmp = T2t1;
		T2t1 = T2t2;
		T2t2 = tmp;
	}

	if (T1t2 < T2t1 || T2t2 < T1t1)
	{

		return false;
	}

	return true;
}

bool CollisionUtilities::IntersectTriangles(TriangleCollider * A, TriangleCollider * B)
{
	Vector3 N1, N2;
	float d1, d2;
	float distances1[3], distances2[3];

	Vector3 t1_points[3];
	Vector3 t2_points[3];

	for (int i = 0; i < 3; i++)
	{
		t1_points[i] = A->getPointAtIndex(i);
		t2_points[i] = B->getPointAtIndex(i);
	}


	N2 = cross(t2_points[1] - t2_points[0], t2_points[2] - t2_points[0]);
	d2 = -1 * dot(N2, t2_points[0]);

	//calculate distances of vertices of one triangle from a plane of second triangle 
	for (int i = 0; i < 3; i++)
	{
		distances1[i] = dot(N2, t1_points[i]) + d2;
	}

	//if all have the same sign, there is noc collision
	if (distances1[0] > 0 && distances1[1] > 0 && distances1[2] > 0)
	{
		return false;
	}
	else if (distances1[0] < 0 && distances1[1] < 0 && distances1[2] < 0)
	{
		return false;
	}
	//if the distance is 0 that means the point is on the plane directly
	//meaning they probably share a point or an edge.
	//so far I am going to disregard it as well
	else if (distances1[0] == 0 || distances1[1] == 0 || distances1[2] == 0)
	{
		return false;
	}

	//same teste are done for other triangle... 
	//not sure if the second one is necessery

	N1 = cross(t1_points[1] - t1_points[0], t1_points[2] - t1_points[0]);
	d1 = -1 * dot(N1, t1_points[0]);

	for (int i = 0; i < 3; i++)
	{
		distances2[i] = dot(N1, t2_points[i]) + d1;
	}

	if (distances2[0] > 0 && distances2[1] > 0 && distances2[2] > 0)
	{
		return false;
	}
	else if (distances2[0] < 0 && distances2[1] < 0 && distances2[2] < 0)
	{
		return false;
	}
	else if (distances2[0] == 0 || distances2[1] == 0 || distances2[2] == 0)
	{
		return false;
	}

	//the intersection of planes is a line
	// line = a point on it + cross of N1xN2
	Vector3 D;
	D = cross(N1, N2);

	Vector3 T1_p, T2_p;

	T1_p.x = dot(D, t1_points[0]);
	T1_p.y = dot(D, t1_points[1]);
	T1_p.z = dot(D, t1_points[2]);

	T2_p.x = dot(D, t2_points[0]);
	T2_p.y = dot(D, t2_points[1]);
	T2_p.z = dot(D, t2_points[2]);

	float T1t1, T1t2, T2t1, T2t2;

	computeTriangleIntersectionIntervals(T1_p, distances1, T1t1, T1t2);
	computeTriangleIntersectionIntervals(T2_p, distances2, T2t1, T2t2);

	//sort the intervals so that the smaller number is on the left
	float tmp = 0;
	if (T1t1 > T1t2)
	{
		tmp = T1t1;
		T1t1 = T1t2;
		T1t2 = tmp;
		tmp = 0;
	}

	if (T2t1 > T2t2)
	{
		tmp = T2t1;
		T2t1 = T2t2;
		T2t2 = tmp;
	}

	if (T1t2 < T2t1 || T2t2 < T1t1)
	{

		return false;
	}

	return true;
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

void CollisionUtilities::computeTriangleIntersectionIntervals(Vector3 projections, float dist[], float & t1, float & t2)
{
	if (dist[0]*dist[1] > 0.0f) 
	{ 
		//if d0 and d1 have the same signs means that d2 is on the other side
		t1 = projections.x + (projections.z - projections.x)*(dist[0] / (dist[0] - dist[2]));
		t2 = projections.y + (projections.z - projections.y)*(dist[1] / (dist[1] - dist[2]));
	} 
	else if (dist[0] * dist[2] > 0.0f)
	{ 
		t1 = projections.x + (projections.y - projections.x)*(dist[0] / (dist[0] - dist[1]));
		t2 = projections.z + (projections.y - projections.z)*(dist[2] / (dist[2] - dist[1]));
	} 
	else if (dist[1] * dist[2] > 0.0f)
	{ 
		t1 = projections.y + (projections.x - projections.y)*(dist[1] / (dist[1] - dist[0]));
		t2 = projections.z + (projections.x - projections.z)*(dist[2] / (dist[2] - dist[0]));
	} 






}

void CollisionUtilities::Vector3tofloatArray(double arr[], Vector3 vec)
{
	arr[0] = vec.x;
	arr[1] = vec.y;
	arr[2] = vec.z;
}
