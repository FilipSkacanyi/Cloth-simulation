#include "Scene.h"
#include "Grid.h"


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

	
	m_cloth = new Cloth();
	m_cloth->Initialise(renderer, 5, 5);
	m_cloth->setPosition(DirectX::XMFLOAT3(0, 0, 0));

	Cube* sphere = new Cube();
	sphere->Init(renderer, "cube.obj", DirectX::XMFLOAT4(1, 0, 0, 1));
	sphere->setGravity(0);
	sphere->setScale(0.5, 0.5, 0.5);

	m_objectsInScene.push_back(sphere);
	
	m_grid = std::make_unique<Grid>(10,10,10,1);

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

	if (input->IsKeyDown(VK_NUMPAD9))
	{
		float f = 30 * dt;
		DirectX::XMFLOAT3 rot = m_objectsInScene[1]->getRotation();
		rot.y -= f;
		m_objectsInScene[1]->setRotation(rot);
	}
	if (input->IsKeyDown(VK_NUMPAD6))
	{
		float f =  1* dt;
		DirectX::XMFLOAT3 pos = m_objectsInScene[1]->getPosition();
		pos.x -= f;
		m_objectsInScene[1]->setPosition(pos);
	}

	if (input->IsKeyDown(VK_SPACE))
	{
		ball_throw += dt;
		if (ball_throw > 2)
		{
			ball_throw = 0;

			Sphere* obj = new Sphere();
			obj->Init(m_renderer, "cube.obj", DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			obj->setGravity(1);
			obj->setPosition(m_camera->getPosition());
			obj->setRotation(0, 0, 0);
			obj->setScale(1, 1, 1);

			DirectX::XMFLOAT3 force = DirectX::XMFLOAT3(m_camera->getForward().x * 10, m_camera->getForward().y * 10, m_camera->getForward().z * 10);
			//obj->AddForce(force);
			m_objectsInScene.push_back(obj);
		}
	}
}

void Scene::Tick(double dt)
{
	m_cloth->Tick(dt, m_renderer);
	
	//DirectX::XMFLOAT3 tmp = DirectX::XMFLOAT3(m_objectsInScene[1]->getPosition().x - 0.0001f, m_objectsInScene[1]->getPosition().y, m_objectsInScene[1]->getPosition().z);
	//m_objectsInScene[1]->setPosition(tmp);

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Tick(dt);
	}
	//m_objectsInScene[0]->resetVelocity(ALL_AXIS);

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

	m_cloth->Render(m_renderer);
}
