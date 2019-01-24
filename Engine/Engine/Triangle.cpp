#include "Triangle.h"
#include <DirectXMath.h>


Triangle::Triangle()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Triangle::~Triangle()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}


	if (m_points)
	{
		delete[] m_points;
		m_points = nullptr;
	}
}

void Triangle::Init(Renderer * renderer, DirectX::XMFLOAT3 points[], DirectX::XMFLOAT4 color)
{
	m_points = new Vector3[3];
	Vertex vertices[3];
	unsigned long indices[3];

	// Load the vertex array with data.
	vertices[0].position = points[0];  // Bottom left.
	vertices[0].color = color;

	vertices[1].position = points[1];  // Top middle.
	vertices[1].color = color;

	vertices[2].position = points[2];  // Bottom right.
	vertices[2].color = color;

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	m_model = renderer->createRawModel(vertices, 3, indices, 3);

	for (int i = 0; i < 3; i++)
	{
		m_points[i] = vertices[i].position;
	}

	
}

void Triangle::Tick(float dt)
{

	m_model->setPosition(m_position);
	m_model->setRotation(m_rotation);
	m_model->setScale(m_scale);
}
