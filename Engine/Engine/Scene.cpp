#include "Scene.h"
#include "Grid.h"
#include "ClothPoint.h"


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

	m_grid = std::make_unique<Grid>(10, 20, 10,1, renderer);

	m_camera = new Camera();
	m_camera->setPosition(10.0f, 6.0f, -5.0f);
	m_camera->setRotation(0, 10, 0);

	
	m_cloth = new Cloth();

	int clothWidth = 10, clothHeigth = 10;

	m_cloth->Initialise(renderer, clothWidth, clothHeigth,0.3, m_objectsInScene);
	m_cloth->setPosition(DirectX::XMFLOAT3(5, 12, 5));
	

	Sphere* sphere = new Sphere();
	sphere->Init(renderer, "cube.obj", DirectX::XMFLOAT4(1, 0, 0, 1));
	sphere->setGravity(0);
	sphere->setPosition(DirectX::XMFLOAT3(5, 12, 5));
	sphere->setScale(0.25, 0.25, 0.25);

	//m_objectsInScene.push_back(sphere);
	
	m_grid->addObject(sphere);

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
			obj->setScale(2,2, 2);

			Vector3 force;
			force = DirectX::XMFLOAT3(m_camera->getForward().x * 10, m_camera->getForward().y * 10, m_camera->getForward().z * 10);
			obj->AddForce(force);
			m_objectsInScene.push_back(obj);
		}
	}
}

void Scene::Tick(double dt)
{
	for (int i = 0; i < m_cloth->getWidth() * m_cloth->getHeigth(); i++)
	{
		m_grid->addObject(m_cloth->getClothpointAtIndex(i));
	}

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_grid->addObject(m_objectsInScene[i]);
	}

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Tick(dt);
	}

	m_cloth->Tick(dt, m_renderer);
	
		//collisions
	m_grid->handleCollisions();

	//generate view matrix
	m_camera->Tick();

	//clear grid
	m_grid->clearAllCells();

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
		Object* obj = dynamic_cast<Object*>(m_objectsInScene[i]);

		if (obj)
		{
		 obj->Render(m_renderer);
		}
		
	}

	m_cloth->Render(m_renderer);

	//m_grid->Render(m_renderer);
}
