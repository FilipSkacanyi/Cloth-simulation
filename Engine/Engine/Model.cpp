#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
}

bool Model::Init(ID3D11Buffer* vertexBuffer)
{
	m_vertexBuffer = vertexBuffer;

	return false;
}

ID3D11Buffer * Model::getVertexBuffer()
{
	return m_vertexBuffer;
}
