#include "Object.h"
#include "OBJ_Loader.h"



Object::Object()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Object::~Object()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}

	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}
}

void Object::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color)
{
	

	objl::Loader loader;
	loader.LoadFile(fileName);

	//go trough the loaded data and translate it to my dat types;
	
	int vertcount = loader.LoadedVertices.size();
	int indcount = loader.LoadedIndices.size();
	Vertex* vertices1 = new Vertex[vertcount];
	unsigned long* indices1 = new unsigned long[indcount];

	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		//loader.LoadedVertices[i].Position;
		vertices1[i].position = DirectX::XMFLOAT3(loader.LoadedVertices[i].Position.X, 
												loader.LoadedVertices[i].Position.Y,
												loader.LoadedVertices[i].Position.Z);
		vertices1[i].color = DirectX::XMFLOAT4(rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	
	for (int i = 0; i < loader.LoadedIndices.size(); i++)
	{
		indices1[i] = loader.LoadedIndices[i];
	}

	
	m_model = renderer->createRawModel(vertices1, vertcount, indices1, indcount);

	
	delete[] vertices1;
	delete[] indices1;

	

}


void Object::Tick(double dt)
{ 
	GameObject::Tick(dt);

	
	


	m_model->setPosition(m_position);
	m_model->setRotation(m_rotation);
	m_model->setScale(m_scale);

	

}

void Object::Render(Renderer * renderer)
{
	renderer->renderModel(m_model);
}



void Object::resetVelocity(VelocityAxis axis)
{
	switch (axis)
	{
	case VelocityAxis::X_AXIS:
	{
		
		break;
	}
	case VelocityAxis::Y_AXIS:
	{
		break;
	}
	case VelocityAxis::Z_AXIS:
	{
		break;
	}
	case VelocityAxis::ALL_AXIS:
	{
		m_velocity = DirectX::XMFLOAT3(0, 0, 0);
		break;
	}

	}
}








