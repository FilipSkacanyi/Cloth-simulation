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

	if (m_test_model)
	{
		delete m_test_model;
		m_test_model = nullptr;
	}

	if (m_test_model1)
	{
		delete m_test_model1;
		m_test_model1 = nullptr;
	}
}

bool Scene::Init(Renderer * renderer)
{
	m_renderer = renderer;

	m_camera = new Camera();
	m_camera->setPosition(1.0f, 2.0f, -6.0f);
	m_camera->setRotation(0, 10, 0);

	Vertex vertices[] =
	{
		{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};

	// Create index buffer
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6,
	};

	m_test_model = m_renderer->createRawModel(vertices, 8, indices, 36);

	m_test_model1 = m_renderer->createRawModel(vertices, 8, indices, 36);
	m_test_model1->setPosition(3, 0, 0);
	m_test_model1->setRotation(0, 90, 0);
	m_test_model1->setScale(1, 1, 1.5);
	return true;
}

void Scene::Tick()
{
	m_test_model->Tick();
	m_test_model1->Tick();
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
	m_renderer->renderModel(m_test_model);
	m_renderer->renderModel(m_test_model1);
}
