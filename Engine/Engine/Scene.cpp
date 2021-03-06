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
}

bool Scene::Init(Renderer * renderer)
{
	m_renderer = renderer;

	//create grid
	m_grid = std::make_unique<Grid>(18, 27, 9,3, renderer);

	m_camera = new Camera();
	m_camera->setPosition(13.0f, 13.0f, 1.0f);
	m_camera->setRotation(0, 0, 0);

	
	m_cloth = new Cloth();
	int clothWidth = 9, clothHeigth = 9;
	m_cloth->Initialise(renderer, clothWidth, clothHeigth,0.3);
	m_cloth->setPosition(Vector3(13, 12, 5));
	

	Sphere* sphere = new Sphere();
	sphere->Init(renderer, "./Resources/sphere.obj", DirectX::XMFLOAT4(1, 0, 0, 1), L"./Resources/red.png");
	sphere->setGravity(0);
	sphere->setPosition(Vector3(13, 11, 7));
	sphere->setScale(0.7, 0.7, 0.7);
	sphere->setKinematic(true);

	objptr = sphere;

	m_objectsInScene.push_back(sphere);
	

	Cube* bed = new Cube();
	bed->Init(renderer, "./Resources/RPG-bed.obj", DirectX::XMFLOAT4(1, 0, 0, 1), L"./Resources/Wooden.jpg");
	bed->setGravity(0);
	bed->setPosition(Vector3(16, 5, 7));
	bed->setRotation(0, 180, 0);
	bed->setScale(2, 2, 2);
	bed->setKinematic(true);

	Cube* drawer = new Cube();
	drawer->Init(renderer, "./Resources/drawer.obj", DirectX::XMFLOAT4(1, 0, 0, 1), L"./Resources/Wooden.jpg");
	drawer->setGravity(0);
	drawer->setPosition(Vector3(0, 2, 2));
	drawer->setRotation(0, 90, 0);
	drawer->setScale(0.1f, 0.1f, 0.1f);
	drawer->setKinematic(true);
	
	Cube* room = new Cube();
	room->Init(renderer, "./Resources/cube.obj", DirectX::XMFLOAT4(1, 0, 0, 1), L"./Resources/wall.png");
	room->setGravity(0);
	room->setPosition(Vector3(10, 15, 2));
	room->setRotation(0, 0, 0);
	room->setScale(25, 25, 25);
	room->setKinematic(true);


	m_objectsInScene.push_back(bed);
	m_objectsInScene.push_back(drawer);
	m_objectsInScene.push_back(room);

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
	}
	if (input->IsKeyDown(VK_NUMPAD3))
	{
		float f = 1 * dt;
		Vector3 pos = objptr->getPosition();
		pos.z += f;
		objptr->setPosition(pos);
	}

	//when you hold space for 2 secods, you throw the sphere in the scene
	if (input->IsKeyDown(VK_SPACE))
	{
		ball_throw += dt;
		if (ball_throw > 2)
		{
			ball_throw = 0;

			Sphere* obj = static_cast<Sphere*>(objptr);
			
			obj->setKinematic(false);
			obj->resetVelocity(VelocityAxis::ALL_AXIS);
			obj->setGravity(1);
			obj->setPosition(Vector3(m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z));
			obj->setRotation(0, 0, 0);
			obj->setScale(0.7,0.7,0.7);

			Vector3 force;
			force = m_camera->getForward();
			force = force * 100;
			obj->AddForce(force);
		}
	}
}

void Scene::Tick(float dt)
{
	//add all objects that should check collision into the grid
	for (int i = 0; i < m_cloth->getTriangleCount(); i++)
	{
		m_grid->addObject(m_cloth->getClothTriangleAtIndex(i));
	}
	for (int i = 0; i < m_cloth->getpointCount(); i++)
	{
		m_grid->addObject(m_cloth->getClothpointAtIndex(i));
	}

	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_grid->addObject(m_objectsInScene[i]);
	}


	//update all objects
	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		m_objectsInScene[i]->Tick(dt);
	}

	m_cloth->Tick(dt, m_renderer);
	
	//collisions
	//grid does all the collision handling
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
	//draw stuff on the screen
	for (int i = 0; i < m_objectsInScene.size(); i++)
	{
		Object* obj = dynamic_cast<Object*>(m_objectsInScene[i]);

		if (obj)
		{
		obj->Render(m_renderer);
		}	
	}

	m_cloth->Render(m_renderer);


	//uncomment this code if you want to see the spatial grid rendered
	/*m_renderer->WireframeRendering();
	m_grid->Render(m_renderer);
	m_renderer->SolidRendering();*/
}
