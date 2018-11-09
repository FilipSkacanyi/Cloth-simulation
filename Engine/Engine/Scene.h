#pragma once

#include "Cube.h"
#include "Sphere.h"
#include <vector>
#include "Input.h"
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

	std::vector<Object*> m_objectsInScene;

	Renderer* m_renderer = nullptr;
	Camera* m_camera = nullptr;

	float ball_throw = 0;
};

