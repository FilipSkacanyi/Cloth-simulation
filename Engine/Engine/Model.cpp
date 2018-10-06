#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
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
