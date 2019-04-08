#pragma once

#include "Cube.h"
#include "Sphere.h"
#include <vector>
#include "Input.h"
#include "Cloth.h"
#include <memory>

#include "Spring.h"

class Grid;

class Scene
{
public:
	Scene();
	~Scene();

	bool Init(Renderer* renderer);
	void input(Input* input, double dt);
	void Tick(float dt);
	void Render();

private:

	std::vector<GameObject*> m_objectsInScene;
	std::vector<Object*> m_renderables;

	Renderer* m_renderer = nullptr;
	Camera* m_camera = nullptr;

	GameObject * objptr = nullptr;

	Cloth* m_cloth = nullptr;

	Spring* spring = nullptr;

	Triangle * triangle1 = nullptr;
	Triangle * triangle2 = nullptr;

	std::unique_ptr<Grid> m_grid = nullptr;

	float ball_throw = 0;
};

