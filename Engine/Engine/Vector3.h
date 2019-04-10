#pragma once
#include <DirectXMath.h>

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

	float Magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3& operator= (const Vector3& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
	Vector3& operator= (const DirectX::XMFLOAT3& Float3) { x = Float3.x; y = Float3.y; z = Float3.z; return *this; }
	Vector3 operator+ (const Vector3 Float3) { return Vector3(x + Float3.x, y + Float3.y, z + Float3.z); }
	Vector3 operator- (const Vector3 Float3) { return Vector3(x - Float3.x, y - Float3.y, z - Float3.z); }
	Vector3 operator* (const float Float) { return Vector3(x * Float, y * Float, z * Float); }
	Vector3 operator/ (const float Float) { return Vector3(x / Float, y / Float, z / Float); }

};