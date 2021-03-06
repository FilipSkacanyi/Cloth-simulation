#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::setAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = DirectX::XMFLOAT4(red, green, blue, alpha);
}

void Light::setDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = DirectX::XMFLOAT4(red, green, blue, alpha);

}

void Light::setDirection(float x, float y, float z)
{
	m_direction = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT4 Light::GetAmbientColor()
{
	return m_ambientColor;
}

DirectX::XMFLOAT4 Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

DirectX::XMFLOAT3 Light::GetDirection()
{
	return m_direction;
}
