#pragma once

#include "Renderer.h"
#include "CollisionUtilities.h"

#include <vector>
#include <memory>
class ClothPoint;
class Spring;
class GameObject;
class ClothTriangle;

class Cloth
{
public:
	Cloth();
	~Cloth();
	void Tick(double dt, Renderer* renderer);
	void Render(Renderer* renderer);
	bool Initialise(Renderer* renderer,int rows, int cols, float distannce, std::vector<GameObject*>& objects_in_scene);

	ClothPoint* getClothpointAtIndex(int i);
	void setPosition(Vector3 pos);
	Vector3 getPosition() { return m_position; }

	

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }

private:
	void selfCollision(float dt);


	int m_width, m_heigth;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Model* m_model = nullptr;

	std::vector<std::unique_ptr<ClothPoint>> m_points;
	std::vector<std::unique_ptr<ClothTriangle>> m_triangles;
	std::vector<std::unique_ptr<Spring>> m_springs;
};

