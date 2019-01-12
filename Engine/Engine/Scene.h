#pragma once

#include "Cube.h"
#include "Sphere.h"
#include <vector>
#include "Input.h"
#include "Cloth.h"
#include <memory>

class Grid;

class Scene
{
public:
	Scene();
	~Scene();

	bool Init(Renderer* renderer);
	void input(Input* input, double dt);
	void Tick(double dt);
	void Render();

private:

	std::vector<GameObject*> m_objectsInScene;

	Renderer* m_renderer = nullptr;
	Camera* m_camera = nullptr;

	GameObject * objptr = nullptr;

	Cloth* m_cloth = nullptr;

	std::unique_ptr<Grid> m_grid = nullptr;

	float ball_throw = 0;
};

