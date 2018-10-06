#include "Model.h"



Model::Model()
{
	position = DirectX::XMFLOAT3(2, 0, 0);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
	scale = DirectX::XMFLOAT3(1, 1, 1);
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
	rotation.y += 0.0001;
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
