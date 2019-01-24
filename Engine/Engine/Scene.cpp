#include "Scene.h"
#include "Grid.h"
#include "ClothPoint.h"
#include "ClothTriangle.h"
#include "Triangle.h"


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

	if (spring)
	{
		delete spring;
		spring = nullptr;
	}
}

bool Scene::Init(Renderer * renderer)
{
	m_renderer = renderer;

	m_grid = std::make_unique<Grid>(27, 27, 27,3, renderer);

	m_camera = new Camera();
	m_camera->setPosition(5.0f, 13.0f, 1.0f);
	m_camera->setRotation(0, 0, 0);

	
	m_cloth = new Cloth();

	int clothWidth = 10, clothHeigth = 10;

	m_cloth->Initialise(renderer, clothWidth, clothHeigth,0.3, m_objectsInScene);
	m_cloth->setPosition(Vector3(5, 12, 5));
	

	Sphere* sphere = new Sphere();
	sphere->Init(renderer, "sphere.obj", DirectX::XMFLOAT4(1, 0, 0, 1));
	sphere->setGravity(0);
	sphere->setPosition(Vector3(5, 11, 7));
	sphere->setScale(0.7, 0.7, 0.7);

	objptr = sphere;

	m_objectsInScene.push_back(sphere);
	

	Cube* cube = new Cube();
	cube->Init(renderer, "cube.obj", DirectX::XMFLOAT4(1, 0, 0, 1));
	cube->setGravity(0);
	cube->setPosition(Vector3(15, 11, 7));
	cube->setScale(1, 1, 1);
	cube->setKinematic(true);


	Cube* cube1 = new Cube();
	cube1->Init(renderer, "cube.obj", DirectX::XMFLOAT4(1, 0, 0, 1));
	cube1->setGravity(1);
	cube1->setPosition(Vector3(15, 1, 7));
	cube1->setScale(1, 1, 1);
	

	//objptr = cube1;

	spring = new Spring();
	spring->assignPoints(cube, cube1, 5);

	m_objectsInScene.push_back(cube);
	m_objectsInScene.push_back(cube1);
	//m_grid->addObject(sphere);

	DirectX::XMFLOAT3 t1[] = {
	DirectX::XMFLOAT3(-1,-1,1),
	DirectX::XMFLOAT3(0,1,0),
	DirectX::XMFLOAT3(1,-1,0)
	};

	DirectX::XMFLOAT3 t2[] = {
	DirectX::XMFLOAT3(-1,0,-1),
	DirectX::XMFLOAT3(1,0,1),
	DirectX::XMFLOAT3(1,0,-1)
	};
	triangle1 = new Triangle();
	triangle1->Init(renderer, t1, DirectX::XMFLOAT4(1, 0, 0, 1));
	triangle1->setPosition(Vector3(5, 5, 5));
	triangle1->setGravity(0);

	triangle2 = new Triangle();
	triangle2->Init(renderer, t2, DirectX::XMFLOAT4(0, 1, 0, 1));
	triangle2->setPosition(Vector3(5, 4.5, 5));
	triangle2->setGravity(0);

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
		float f = 10 * dt;
		DirectX::XMFLOAT3 pos = m_camera->getPosition();
		pos.y += f;
		m_camera->setPosition(pos);
	}
	if (input->IsKeyDown(VK_NUMPAD2))
	{
		float f = 10 * dt;
		DirectX::XMFLOAT3 pos = m_camera->getPosition();
		pos.y -= f;
		m_camera->setPosition(pos);
	}
	
	if (input->IsKeyDown(VK_NUMPAD5))
	{
		//forward
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getForward();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x + forward.x * 30 * dt), (camerapos.y + forward.y * 30 * dt), (camerapos.z + forward.z * 30 * dt)));
	}

	if (input->IsKeyDown(VK_NUMPAD0))
	{
		//backwards
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getForward();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x - forward.x * 30 * dt), (camerapos.y - forward.y * 30 * dt), (camerapos.z - forward.z * 30 * dt)));

	}
	if (input->IsKeyDown(VK_NUMPAD6))
	{
		//right
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getRight();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x + forward.x * 30 * dt), (camerapos.y + forward.y * 30 * dt), (camerapos.z + forward.z * 30 * dt)));
	}

	if (input->IsKeyDown(VK_NUMPAD4))
	{
		//left
		DirectX::XMFLOAT3 camerapos = m_camera->getPosition();
		DirectX::XMFLOAT3 forward = m_camera->getRight();
		m_camera->setPosition(DirectX::XMFLOAT3((camerapos.x - forward.x * 30 * dt), (camerapos.y - forward.y * 30 * dt), (camerapos.z - forward.z * 30 * dt)));

	}
	if (input->IsKeyDown(VK_NUMPAD1))
	{
		float f =  1* dt;
		Vector3 pos = objptr->getPosition();
		pos.z -= f ;
		objptr->setPosition(pos);

		Vector3 pos2 = triangle1->getPosition();
		pos2.y -= f;
		triangle1->setPosition(pos2);
	}
	if (input->IsKeyDown(VK_NUMPAD3))
	{
		float f = 1 * dt;
		Vector3 pos = objptr->getPosition();
		pos.z += f;
		objptr->setPosition(pos);

		Vector3 pos2 = triangle1->getPosition();
		pos2.y += f;
		triangle1->setPosition(pos2);
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
			obj->setPosition(Vector3(m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z));
			obj->setRotation(0, 0, 0);
			obj->setScale(2,2, 2);

			Vector3 force;
			force = force * 100000;
			obj->AddForce(force);
			m_objectsInScene.push_back(obj);
		}
	}
}

void Scene::Tick(double dt)
{
	for (int i = 0; i < m_cloth->getTriangleCount(); i++)
	{
		m_grid->addObject(m_cloth->getClothTriangleAtIndex(i));
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
	
	triangle1->Tick(dt);
	triangle2->Tick(dt);

	if (CollisionUtilities::IntersectTriangles(triangle1, triangle2))
	{
		OutputDebugString("there was triangle collision\n");
	}
	else
	{
		OutputDebugString("no triangle collision\n");
	}


	spring->Tick(dt);
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

	triangle1->Render(m_renderer);
	triangle2->Render(m_renderer);

	//m_grid->Render(m_renderer);
}
