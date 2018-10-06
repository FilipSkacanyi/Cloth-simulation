#include "Model.h"



Model::Model()
{
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

bool Model::Init(ID3D11Buffer* vertexBuffer, int vertexNum, ID3D11Buffer* indexBuffer)
{
	m_vertexBuffer = vertexBuffer;
	m_vertexNumber = vertexNum;
	m_indexBuffer = indexBuffer;
	return false;
}

ID3D11Buffer * Model::getVertexBuffer()
{
	return m_vertexBuffer;
}

ID3D11Buffer * Model::getIndexBuffer()
{
	return m_indexBuffer;
}

int Model::getVertexNumber()
{
	return m_vertexNumber;
}
