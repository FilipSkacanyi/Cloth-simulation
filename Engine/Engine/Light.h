#pragma once
#include <DirectXMath.h>

class Light
{
public:
	Light();
	~Light();

	void setDiffuseColor(float red, float green, float blue, float alpha);
	void setDirection(float x, float y, float z);

	DirectX::XMFLOAT4 GetDiffuseColor();
	DirectX::XMFLOAT3 GetDirection();

private:
	DirectX::XMFLOAT4 m_diffuseColor;
	DirectX::XMFLOAT3 m_direction;
};
