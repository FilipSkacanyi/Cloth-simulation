#pragma once

#include "Renderer.h"

class Scene
{
public:
	Scene();
	~Scene();

	bool Init(Renderer* renderer);

	void Tick();
	void Render();

private:

	Renderer* m_renderer = nullptr;
	Camera* m_camera = nullptr;
	Model* m_test_model = nullptr;
	Model* m_test_model1 = nullptr;

};

