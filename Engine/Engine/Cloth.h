#pragma once

#include "Renderer.h"
#include "CollisionUtilities.h"

#include <vector>
#include <memory>
class ClothPoint;
class Spring;
class Cloth
{
public:
	Cloth();
	~Cloth();
	void Tick(double dt, Renderer* renderer);
	void Render(Renderer* renderer);
	bool Initialise(Renderer* renderer,int rows, int cols);

	void setPosition(DirectX::XMFLOAT3 pos) { m_position = pos; }

private:

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;
	Model* m_model = nullptr;

	std::vector<std::unique_ptr<ClothPoint>> m_points;
	std::vector<std::unique_ptr<Spring>> m_springs;
};

