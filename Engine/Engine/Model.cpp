#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
}

bool Model::Init(ID3D11Buffer* vertexBuffer, int vertexNum)
{
	m_vertexBuffer = vertexBuffer;
	m_vertexNumber = vertexNum;

	return false;
}

ID3D11Buffer * Model::getVertexBuffer()
{
	return m_vertexBuffer;
}

int Model::getVertexNumber()
{
	return m_vertexNumber;
}
