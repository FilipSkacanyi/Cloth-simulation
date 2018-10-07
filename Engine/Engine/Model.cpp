#include "Model.h"



Model::Model()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Model::~Model()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}

	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
}

bool Model::Init(ID3D11Buffer* vertexBuffer, int vertexNum, ID3D11Buffer* indexBuffer, int indexNum)
{
	m_vertexBuffer = vertexBuffer;
	m_vertexCount = vertexNum;
	m_indexBuffer = indexBuffer;
	m_indexCount = indexNum;
	return false;
}

void Model::Tick()
{
	m_rotation.y += 0.0001;
}

void Model::setPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
}

void Model::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}

void Model::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void Model::setRotation(DirectX::XMFLOAT3 rot)
{
	m_rotation = rot;
}

void Model::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT3 Model::getPosition()
{
	return m_position;
}

DirectX::XMFLOAT3 Model::getRotation()
{
	return m_rotation;
}

DirectX::XMFLOAT3 Model::getScale()
{
	return m_scale;
}

//void Model::Render(Renderer * renderer)
//{
//}

ID3D11Buffer * Model::getVertexBuffer()
{
	return m_vertexBuffer;
}

ID3D11Buffer * Model::getIndexBuffer()
{
	return m_indexBuffer;
}

int Model::getIndexCount()
{
	return m_indexCount;
}

int Model::getVertexCount()
{
	return m_vertexCount;
}
