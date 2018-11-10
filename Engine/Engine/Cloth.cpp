#include "Cloth.h"
#include "ClothPoint.h"


Cloth::Cloth()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
}


Cloth::~Cloth()
{
}

void Cloth::Tick(double dt, Renderer* renderer)
{
	//m_points[0]->setPosition(DirectX::XMFLOAT3(m_points[0]->getPosition().x - dt, m_points[0]->getPosition().y+dt, m_points[0]->getPosition().z));
	//m_points[1]->setPosition(DirectX::XMFLOAT3(m_points[1]->getPosition().x  , m_points[1]->getPosition().y + dt, m_points[1]->getPosition().z));

	for (int i = 0; i < m_model->getVertexCount(); i++)
	{
		}
	

	m_model->setPosition(m_position);
}

void Cloth::Render(Renderer * renderer)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	Vertex* vertices = new Vertex[m_model->getVertexCount()];

	for (int i = 0; i < m_model->getVertexCount(); i++)
	{
		
		vertices[i].position = m_points[i]->getPosition();
		vertices[i].color = DirectX::XMFLOAT4(1, 0, 0, 1);

	}


	//  Disable GPU access to the vertex buffer data.
	auto m_d3dContext = renderer->getContext();
	m_d3dContext->Map(m_model->getVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//  Update the vertex buffer here.
	memcpy(mappedResource.pData, vertices, sizeof(Vertex) * m_model->getVertexCount());
	//  Reenable GPU access to the vertex buffer data.
	m_d3dContext->Unmap(m_model->getVertexBuffer(), 0);
	delete[] vertices;
	
	renderer->renderModel(m_model);
}

bool Cloth::Initialise(Renderer * renderer, int rows, int cols)
{
	int vertexNum, indexNum;

	vertexNum = rows * cols;
	indexNum = ((rows - 1) * (cols - 1)) * 6;


	Vertex* tmpvert = new Vertex[vertexNum];

	//find the center of cloth given;
	float centerX = 0, centerY = 0;

	centerX = (float)cols / 2 - 0.5f;
	centerY = (float)rows / 2 - 0.5f;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			tmpvert[i*cols + j].position = DirectX::XMFLOAT3(j-centerX, i-centerY, 0);
		    
			//tmpvert[i*cols + j].color = DirectX::XMFLOAT4(rand() % 2, rand() % 2, rand() % 2, 1);
			tmpvert[i*cols + j].color = DirectX::XMFLOAT4(1, 0, 0, 1);
			m_points.push_back(std::make_unique<ClothPoint>());
			m_points[m_points.size() - 1]->setPosition(DirectX::XMFLOAT3(j - centerX, -i + centerY, 0));
		}
	}

	
	unsigned long* tmpind = new unsigned long[indexNum];
	int indices_iterator = 0;
	for (int i = 0; i < rows - 1 ; i++)
	{
		for (int j = 0; j < cols -1 ; j++)
		{
			
			tmpind[indices_iterator++] = i * (cols)+j;
			tmpind[indices_iterator++] = i * (cols)+j + 1;
			tmpind[indices_iterator++] = (i+1) * (cols)+j;

			tmpind[indices_iterator++] = (i + 1) * (cols)+j;
			tmpind[indices_iterator++] = i * (cols)+j + 1;
			tmpind[indices_iterator++] = (i + 1) * (cols)+j +1 ;
			
			


		}
	}

	

	m_model = new Model();
	ID3D11Device* device = renderer->getDevice();
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexNum;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = tmpvert;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
		return FALSE;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned long) * indexNum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	InitData.pSysMem = tmpind;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &indexBuffer)))
		return FALSE;

	m_model->Init(vertexBuffer, vertexNum, indexBuffer, indexNum);

	delete[] tmpvert;
	delete[] tmpind;
}
