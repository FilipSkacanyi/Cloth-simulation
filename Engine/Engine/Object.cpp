#include "Object.h"



Object::Object()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Object::~Object()
{
	if (m_boundingBox)
	{
		delete m_boundingBox;
		m_boundingBox = nullptr;
	}

	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}
}

void Object::Init(Renderer * renderer)
{
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


	m_model = renderer->createRawModel(vertices, 8, indices, 36);

	//create bounding box
	m_boundingBox = new DirectX::BoundingOrientedBox();
	//init bounding box
	m_boundingBox->Center = m_position;
	m_boundingBox->Extents = m_scale;
	DirectX::XMStoreFloat4(&m_boundingBox->Orientation, DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z));
	
}

void Object::Tick(double dt)
{
	m_rotation.y += 0.0001;

	m_model->setPosition(m_position);
	m_model->setRotation(m_rotation);
	m_model->setScale(m_scale);

	//update bounding box
	m_boundingBox->Center = m_position;
	m_boundingBox->Extents = m_scale;
	DirectX::XMStoreFloat4(&m_boundingBox->Orientation, DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z));
}

void Object::Render(Renderer * renderer)
{
	renderer->renderModel(m_model);
}

void Object::setPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
}

void Object::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}

void Object::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void Object::setRotation(DirectX::XMFLOAT3 rot)
{
	m_rotation = rot;
}

void Object::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

void Object::setScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

DirectX::XMFLOAT3 Object::getPosition()
{
	return m_position;
}

DirectX::XMFLOAT3 Object::getRotation()
{
	return m_rotation;
}

DirectX::XMFLOAT3 Object::getScale()
{
	return m_scale;
}

DirectX::BoundingOrientedBox * Object::getBoundingBox()
{
	return m_boundingBox;
}
