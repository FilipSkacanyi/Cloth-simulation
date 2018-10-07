#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		delete m_objectsInScene[i];
		m_objectsInScene[i] = nullptr;
	}
	m_objectsInScene.clear();
}

bool Scene::Init(Renderer * renderer)
{
	m_renderer = renderer;

	m_camera = new Camera();
	m_camera->setPosition(1.0f, 2.0f, -6.0f);
	m_camera->setRotation(0, 10, 0);

	
	Object* obj = new Object();
	obj->Init(renderer);

	Object* obj1 = new Object();
	obj1->Init(renderer);

	obj1->setPosition(4, 0.2, 0);
	obj1->setRotation(0, 0, 0);
	obj1->setScale(0.5, 0.5, 0.5);
	
	m_objectsInScene.push_back(obj);
	m_objectsInScene.push_back(obj1);

	return true;
}

void Scene::Tick()
{

	DirectX::XMFLOAT3 tmp = DirectX::XMFLOAT3(m_objectsInScene[1]->getPosition().x - 0.0001f, m_objectsInScene[1]->getPosition().y, m_objectsInScene[1]->getPosition().z);
	m_objectsInScene[1]->setPosition(tmp);

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Tick();
	}


	DirectX::BoundingOrientedBox* box = m_objectsInScene[1]->getBoundingBox();
	DirectX::ContainmentType type = m_objectsInScene[0]->getBoundingBox()->Contains(*box);

	if (type == DirectX::ContainmentType::INTERSECTS)
	{
		m_objectsInScene[1]->setPosition(4, 0.2, 0);
	}
	//generate view matrix
	m_camera->Tick();

	//get view matrix from camera
	DirectX::XMMATRIX viewMatrix;
	m_camera->getViewMatrix(viewMatrix);

	//update renderers view matrix
	m_renderer->updateViewMatrix(viewMatrix);
}

void Scene::Render()
{
	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Render(m_renderer);
	}
}
