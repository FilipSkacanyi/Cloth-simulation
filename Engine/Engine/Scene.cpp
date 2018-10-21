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

	
	Cube* obj = new Cube();
	obj->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	//obj->setGravity(0);
	obj->setRotation(0, 0, 0);
	
	Cube* obj1 = new Cube();
	obj1->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

	obj1->setPosition(0, 5, 0);
	obj1->setRotation(0, 0, 0);
	obj1->setScale(0.5, 0.5, 0.5);

	Sphere* obj2 = new Sphere();
	obj2->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	//obj2->setGravity(0);
	obj2->setRotation(0, 0, 0);
	obj2->setPosition(2, 0, 0);

	Sphere* obj3 = new Sphere();
	obj3->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	obj3->setRotation(0, 0, 0);
	obj3->setPosition(2, 5, 0);

	Cube* obj4 = new Cube();
	obj4->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	//obj4->setGravity(0);
	obj4->setRotation(0, 0, 0);
	obj4->setPosition(4, 0, 0);

	Sphere* obj5 = new Sphere();
	obj5->Init(renderer, "cube2.txt", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	obj5->setRotation(0, 0, 0);
	obj5->setPosition(3.3, 5, 0.1);
	obj5->setScale(0.5, 0.5, 0.5);

	
	m_objectsInScene.push_back(obj);
	m_objectsInScene.push_back(obj1);
	m_objectsInScene.push_back(obj2);
	m_objectsInScene.push_back(obj3);
	m_objectsInScene.push_back(obj4);
	m_objectsInScene.push_back(obj5);

	return true;
}

void Scene::input(Input * input, double dt)
{
	if (input->IsKeyDown(VK_LEFT))
	{
		DirectX::XMFLOAT3 camerarot = m_camera->getRotation();
		camerarot.x -= 30*dt;
		m_camera->setRotation(camerarot);
	}
	if (input->IsKeyDown(VK_RIGHT))
	{
		DirectX::XMFLOAT3 camerarot = m_camera->getRotation();
		camerarot.x +=  30*dt;
		m_camera->setRotation(camerarot);
	}
	if (input->IsKeyDown(VK_UP))
	{
		DirectX::XMFLOAT3 camerarot = m_camera->getRotation();
		camerarot.y -= 30*dt;
		m_camera->setRotation(camerarot);
	}
	if (input->IsKeyDown(VK_DOWN))
	{
		DirectX::XMFLOAT3 camerarot = m_camera->getRotation();
		camerarot.y += 30*dt;
		m_camera->setRotation(camerarot);
	}

	if (input->IsKeyDown(VK_NUMPAD8))
	{
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getForward();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x + forward.x *30* dt), (camerapos.y + forward.y* 30*dt), (camerapos.z + forward.z*30* dt)));
	}
	if (input->IsKeyDown(VK_NUMPAD2))
	{
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getForward();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x - forward.x* 30* dt), (camerapos.y - forward.y* 30* dt), (camerapos.z - forward.z*30* dt)));
	}
}

void Scene::Tick(double dt)
{
	
	//DirectX::XMFLOAT3 tmp = DirectX::XMFLOAT3(m_objectsInScene[1]->getPosition().x - 0.0001f, m_objectsInScene[1]->getPosition().y, m_objectsInScene[1]->getPosition().z);
	//m_objectsInScene[1]->setPosition(tmp);

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Tick(dt);
	}
	

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		for (int j = i +1; j < m_objectsInScene.size(); j++)
		{
			if (m_objectsInScene[i]->getCollider()->Intersect(m_objectsInScene[j]->getCollider()))
			{
				m_objectsInScene[i]->collision(m_objectsInScene[j]);
				m_objectsInScene[j]->collision(m_objectsInScene[i]);
				//m_objectsInScene[j]->AddForce(DirectX::XMFLOAT3(0, 5, 0));
			}
		}
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
