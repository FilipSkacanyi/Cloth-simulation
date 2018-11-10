
#pragma once
#include <DirectXMath.h>
#include <DirectXCollision.h>

class AlignedBoxCollider;
class SphereCollider;
class OrientedBoxCollider;

struct Vector3
{
	float x, y, z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	void Normalize()
	{
		float mag = sqrt(x * x + y * y + z * z);
		
		if (mag != 0)
		{
			x = x / mag;
			y = y / mag;
			z = z / mag;
		}
	}

	Vector3& operator= (const Vector3& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
	Vector3& operator= (const DirectX::XMFLOAT3& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
	Vector3 operator+ (const Vector3 Float3) { return Vector3(x + Float3.x,y + Float3.y,z + Float3.z); }
	Vector3 operator- (const Vector3 Float3) { return Vector3(x - Float3.x, y - Float3.y, z - Float3.z); }
	Vector3 operator* (const float Float) { return Vector3(x * Float, y * Float, z * Float); }
	Vector3 operator/ (const float Float) { return Vector3(x / Float, y / Float, z / Float); }
	
};

class CollisionUtilities
{
public:
	CollisionUtilities();
	~CollisionUtilities();

	static bool IntersectAlignedBoxes(AlignedBoxCollider* A, AlignedBoxCollider *B);
	static bool IntersectSpheres(SphereCollider* A, SphereCollider* B);
	static bool IntersectBoxSphere(AlignedBoxCollider* box, SphereCollider * sphere);
	static bool IntersectBoxSphere( SphereCollider * sphere, AlignedBoxCollider* box);
	static bool IntersectAABB_OBB(AlignedBoxCollider* AABB, OrientedBoxCollider* obox);
	static bool IntersectAABB_OBB(OrientedBoxCollider* obox, AlignedBoxCollider* AABB);
	static bool IntersectOrientedBoxes(OrientedBoxCollider* obox1, OrientedBoxCollider* obox2);
	static bool IntersectOrientedBoxSphere(OrientedBoxCollider* obox, SphereCollider* sphere);
	static bool IntersectOrientedBoxSphere(SphereCollider* sphere, OrientedBoxCollider* obox);

private:

	static float Min(float f1, float f2);
	static float Max(float f1, float f2);
	static float dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static float dot(Vector3 A, Vector3 B);
	static DirectX::XMFLOAT3 cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static Vector3 cross(Vector3 A, Vector3 B);
	static float absoluteValue(float f);
	static bool intersectRange(float min0, float max0, float min1, float max1);
	static bool checkSeparatingAxes(Vector3 distance, Vector3 current_axis, 
									Vector3 Ax, Vector3 Ay, Vector3 Az, Vector3 Bx, Vector3 By, Vector3 Bz,
									float WA, float HA, float DA, float WB, float HB, float DB);
};








