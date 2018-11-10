#pragma once

#include <DirectXMath.h>
class Cloth;
class ClothPoint
{
public:
	ClothPoint();
	~ClothPoint();

	void Tick();
	DirectX::XMFLOAT3 getPosition();
	void setParent(Cloth* parent_) { m_parent = parent_; }
	void setPosition(DirectX::XMFLOAT3 pos);


private:
	DirectX::XMFLOAT3 m_position;
	Cloth* m_parent = nullptr;
};

