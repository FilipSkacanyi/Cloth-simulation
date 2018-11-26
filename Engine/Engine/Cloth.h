#pragma once

#include "Renderer.h"
#include "CollisionUtilities.h"

#include <vector>
#include <memory>
class ClothPoint;
class Spring;
class GameObject;

class Cloth
{
public:
	Cloth();
	~Cloth();
	void Tick(double dt, Renderer* renderer);
	void Render(Renderer* renderer);
	bool Initialise(Renderer* renderer,int rows, int cols, float distannce, std::vector<GameObject*>& objects_in_scene);

	ClothPoint* getClothpointAtIndex(int i);
	void setPosition(DirectX::XMFLOAT3 pos);
	DirectX::XMFLOAT3 getPosition() { return m_position; }

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }

private:
	int m_width, m_heigth;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;
	Model* m_model = nullptr;

	std::vector<std::unique_ptr<ClothPoint>> m_points;
	std::vector<std::unique_ptr<Spring>> m_springs;
};

