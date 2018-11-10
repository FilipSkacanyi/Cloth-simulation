#include "ClothPoint.h"
#include "Cloth.h"


ClothPoint::ClothPoint()
{
}


ClothPoint::~ClothPoint()
{
}

void ClothPoint::Tick()
{
}

DirectX::XMFLOAT3 ClothPoint::getPosition()
{
	return m_position;
}

void ClothPoint::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}
