#include "ClothTriangle.h"
#include "ClothPoint.h"
#include "TriangleCollider.h"
#include "Timer.h"
#include "Texture.h"



ClothTriangle::ClothTriangle()
{
	m_collider = new TriangleCollider();
	m_collider->Init(ColliderType::TRIANGLE);

	m_texturecoords.reserve(3);
	m_points.reserve(3);
	m_texturecoords.push_back(DirectX::XMFLOAT2(0.0f, 1.0f));
	m_texturecoords.push_back(DirectX::XMFLOAT2(0.5f, 0.0f));
	m_texturecoords.push_back(DirectX::XMFLOAT2(1.0f, 1.0f));
	

}


ClothTriangle::~ClothTriangle()
{
}

void ClothTriangle::addPoints(ClothPoint * a, ClothPoint * b, ClothPoint * c)
{
	if (m_points.size() > 0)
	{
		m_points.clear();
	}

	m_points.push_back(a);
	m_points.push_back(b);
	m_points.push_back(c);
}

void ClothTriangle::setTextureCoords(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b, DirectX::XMFLOAT2 c)
{
	m_texturecoords[0] = a;
	m_texturecoords[1] = b;
	m_texturecoords[2] = c;

}

bool ClothTriangle::Init(Renderer* renderer, Texture * texture)
{
	Vertex vertices[3];
	unsigned long indices[3];

	for (int i = 0; i < 3; i++)
	{
		Vector3 pos = m_points[i]->getPosition();
		vertices[i].position = DirectX::XMFLOAT3(pos.x, pos.y, pos.z);
		vertices[i].color = DirectX::XMFLOAT4(1, 0, 0, 1);
	}

	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	m_model = new Model();
	m_model->setTexture(texture);
	ID3D11Device* device = renderer->getDevice();
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
		return FALSE;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned long) * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	InitData.pSysMem = indices;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &indexBuffer)))
		return FALSE;

	m_model->Init(vertexBuffer, 3, indexBuffer, 3);



	//m_model = renderer->createRawModel(vertices, 3, indices, 3);


	return false;
}

void ClothTriangle::Render(Renderer * renderer)
{

	

	renderer->renderModel(m_model);


}

void ClothTriangle::recalculateVertices(Renderer * renderer)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//  Disable GPU access to the vertex buffer data.
	auto m_d3dContext = renderer->getContext();
	m_d3dContext->Map(m_model->getVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	Vertex* dataPtr = (Vertex*)mappedResource.pData;

	//Vertex* vertices = new Vertex[m_model->getVertexCount()];

	//DirectX::XMFLOAT3 pos = dataPtr[0].position;

	//calculate the surface normals
	Vector3 A = m_points[0]->getPosition() - m_points[1]->getPosition();
	Vector3 B = m_points[0]->getPosition() - m_points[2]->getPosition();

	Vector3 normal = CollisionUtilities::cross(A, B);

	normal.Normalize();

	for (int i = 0; i < m_model->getVertexCount(); i++)
	{
		Vector3 pos = m_points[i]->getPosition();
		dataPtr[i].position = DirectX::XMFLOAT3(pos.x, pos.y, pos.z);
		dataPtr[i].color = DirectX::XMFLOAT4(1, 0, 0, 1);
		dataPtr[i].normal = DirectX::XMFLOAT3(-normal.x, -normal.y, -normal.z);
		dataPtr[i].texture = m_texturecoords[i];
	}


	//  Update the vertex buffer here.
	//memcpy(mappedResource.pData, vertices, sizeof(Vertex) * m_model->getVertexCount());
	//  Reenable GPU access to the vertex buffer data.
	m_d3dContext->Unmap(m_model->getVertexBuffer(), 0);
	//delete[] vertices;


}


ClothPoint * ClothTriangle::getClothPointAtIndex(int i)
{
	return m_points[i];
}

void ClothTriangle::Tick(float dt)
{
	TriangleCollider* tmp = static_cast<TriangleCollider*>(m_collider);
	tmp->setPoints(m_points[0]->getPosition(), m_points[1]->getPosition(), m_points[2]->getPosition());
}

Vector3 ClothTriangle::getSurfaceNormal()
{
	Vector3 A = m_points[0]->getPosition() - m_points[1]->getPosition();
	Vector3 B = m_points[0]->getPosition() - m_points[2]->getPosition();

	Vector3 normal = CollisionUtilities::cross(A, B);

	normal.Normalize();

	return normal;
}

void ClothTriangle::AddForce(Vector3 force)
{
	for (int i = 0; i < m_points.size(); i++)
	{
		m_points[i]->AddForce(force);
	}
}

void ClothTriangle::collision(GameObject * other)
{
	ClothTriangle* tmp = static_cast<ClothTriangle*>(other);
	//tmp->AddForce();

	//force = mass * acceleration;
	//acceleration = force / mass

	//m_velocity = m_velocity + m_acceleration * dt;
	//velocity +(force /mass) *dt = 0
	//force *dt / mass = -velocity
	//force * dt = -velocity * mass
	//force = -velocity * mass / dt

	for (int i = 0; i < 3; i++)
	{
		ClothPoint* point = tmp->getClothPointAtIndex(i);
		Vector3 velocity = point->getVelocity();

		Vector3 distance = tmp->getPosition() - getPosition();
		float distmag = distance.Magnitude() * 5;
		distance.Normalize();
		point->AddForce(((velocity * (-0.1f) * point->getMass()) / Timer::Instance()->DeltaTime()));
		point->AddForce(distance * (0.1f / distmag));
	}


}

Vector3 ClothTriangle::getPosition()
{
	Vector3 averagePosition;
	  
	for (int i = 0; i < 3; i++)
	{
		averagePosition = averagePosition + m_points[i]->getPosition();
	}

	return averagePosition / 3;
}
