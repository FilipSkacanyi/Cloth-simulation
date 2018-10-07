#pragma once

#include "Object.h"
#include <vector>
class Scene
{
public:
	Scene();
	~Scene();

	bool Init(Renderer* renderer);

	void Tick();
	void Render();

private:

	std::vector<Object*> m_objectsInScene;

	Renderer* m_renderer = nullptr;
	Camera* m_camera = nullptr;


};

