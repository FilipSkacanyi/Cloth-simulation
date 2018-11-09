#pragma once

#include <DirectXMath.h>

class ClothPoint
{
public:
	ClothPoint();
	~ClothPoint();

	void Tick();
	DirectX::XMFLOAT3 getPosition();
	void setPosition(DirectX::XMFLOAT3 pos);

private:
	DirectX::XMFLOAT3 m_position;
};

