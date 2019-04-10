#pragma once

#include "Renderer.h"
#include "CollisionUtilities.h"
#include "Texture.h"

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
	void Tick(float dt, Renderer* renderer);
	void Render(Renderer* renderer);
	bool Initialise(Renderer* renderer,int rows, int cols, float distannce);

	ClothPoint* getClothpointAtIndex(int i);
	ClothTriangle* getClothTriangleAtIndex(int i);
	void setPosition(Vector3 pos);
	Vector3 getPosition() { return m_position; }

	int getWidth() { return m_width; }
	int getHeigth() { return m_heigth; }
	int getTriangleCount() { return m_triangle_count; }
	int getpointCount() { return m_point_count; }

	Texture* getTexture();
private:
	
	int m_width, m_heigth, m_triangle_count,m_point_count;
	float m_distance;
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;
	Model* m_model = nullptr;

	Texture* m_texture = nullptr;

	//vectors of unique pointers
	//no worries about releasing
	//this gets done automatically
	std::vector<std::unique_ptr<ClothPoint>> m_points;
	std::vector<std::unique_ptr<ClothTriangle>> m_triangles;
	std::vector<std::unique_ptr<Spring>> m_springs;
};

