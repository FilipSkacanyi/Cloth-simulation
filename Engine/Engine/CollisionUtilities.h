
#pragma once
#include <DirectXMath.h>

class AlignedBoxCollider;
class SphereCollider;

class CollisionUtilities
{
public:
	CollisionUtilities();
	~CollisionUtilities();

	static bool IntersectAlignedBoxes(AlignedBoxCollider* A, AlignedBoxCollider *B);
	static bool IntersectSpheres(SphereCollider* A, SphereCollider* B);
	static bool IntersectBoxSphere(AlignedBoxCollider* box, SphereCollider * sphere);

private:

	static float Min(float f1, float f2);
	static float Max(float f1, float f2);
	static float dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static bool intersectRange(float min0, float max0, float min1, float max1);
};



struct BoundingSphere
{
	float radius;
	DirectX::XMFLOAT3 position;
};

struct AxisAlignedBoundingBox
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 extends;
};



