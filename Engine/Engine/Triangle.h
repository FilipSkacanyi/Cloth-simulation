#pragma once
#include "Object.h"
class Triangle :
	public Object
{
public:
	Triangle();
	~Triangle();

	virtual void Init(Renderer* renderer, DirectX::XMFLOAT3 points[], DirectX::XMFLOAT4 color);
	Vector3 * getPoints() { return m_points; }

	void Tick(float dt);
private:

	Vector3* m_points = nullptr;
};

