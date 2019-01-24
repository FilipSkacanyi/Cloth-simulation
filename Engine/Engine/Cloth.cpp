#include "Cloth.h"
#include "ClothPoint.h"
#include "ClothTriangle.h"
#include "Spring.h"


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

	/*for (int i = 0; i < m_points.size(); i++)
	{
		m_points[i]->Tick(dt);
	}*/
	for (int i = 0; i < m_springs.size(); i++)
	{
		m_springs[i]->Tick(dt);
	}
	
	//selfCollision(dt);

	m_model->setPosition(m_position);
}

void Cloth::Render(Renderer * renderer)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	Vertex* vertices = new Vertex[m_model->getVertexCount()];

	for (int i = 0; i < m_model->getVertexCount(); i++)
	{
		DirectX::XMFLOAT3 temppos = DirectX::XMFLOAT3(m_points[i]->getPosition().x - m_position.x,
			m_points[i]->getPosition().y - m_position.y,
			m_points[i]->getPosition().z - m_position.z);

		//Vector3 temppos = Vector3(m_points[i]->getPosition() - m_position);

		vertices[i].position = temppos;
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

bool Cloth::Initialise(Renderer * renderer, int rows, int cols,float distance, std::vector<GameObject*>& objects_in_scene)
{
	int vertexNum, indexNum;
	m_width = cols;
	m_heigth = rows;
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
			//create a vertex
			tmpvert[i*cols + j].position = DirectX::XMFLOAT3(j*distance -centerX * distance, i*distance -centerY * distance, 0);
		    tmpvert[i*cols + j].color = DirectX::XMFLOAT4(1, 0, 0, 1);

			//create a cloth point based on the same values as the vertex
			m_points.push_back(std::make_unique<ClothPoint>());
			m_points[m_points.size() - 1]->setPosition(Vector3(j*distance - centerX * distance + m_position.x, -i * distance + centerY* distance + m_position.y, 0+ m_position.z));
			m_points[m_points.size() - 1]->setParent(this);
			m_points[m_points.size() - 1]->Init();
			objects_in_scene.push_back(m_points[m_points.size() - 1].get());
		}
	}

	m_points[0]->setKinematic(true);
	m_points[cols - 1]->setKinematic(true);
	

	//assign indices
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

	for (int i = 0; i < indexNum; i +=3 )
	{
		m_triangles.push_back(std::make_unique<ClothTriangle>());
		m_triangles[m_triangles.size() - 1]->addPoints(m_points[tmpind[i]].get(),
														m_points[tmpind[i + 1]].get(),
														m_points[tmpind[i + 2]].get());
	}
	

	//add springs to the mix
	
	for (int i = 0; i < rows; i++)
	{

		for (int j = 0; j < cols; j++)
		{

			ClothPoint* A = nullptr;
			ClothPoint* B = nullptr;
			Spring* currentSpring = nullptr;
			//  i * cols+j;

			/*m_springs.push_back(std::make_unique<Spring>());
			currentSpring = m_springs[m_springs.size() - 1].get();*/
			//the current spring is the last element since we just pushed one back
			//such is life with using unique pointers

			A = m_points[i * cols + j].get();

			if (i != rows - 1) //strait down
			{
				m_springs.push_back(std::make_unique<Spring>());
				currentSpring = m_springs[m_springs.size() - 1].get();
				B = m_points[(i + 1) * cols + j].get();
				currentSpring->assignPoints(A, B,distance);
			
			}

			if (j != 0 && i != rows - 1 ) //bottom left
			{
				m_springs.push_back(std::make_unique<Spring>());
				currentSpring = m_springs[m_springs.size() - 1].get();
				B = m_points[(i+1) * cols + j - 1].get();
				currentSpring->assignPoints(A, B, distance);
				currentSpring->setType(SpringType::DIAGONAL);
			}

			if (j != cols - 1) //right and bottom right
			{
				m_springs.push_back(std::make_unique<Spring>());
				currentSpring = m_springs[m_springs.size() - 1].get();
				B = m_points[i * cols + j + 1].get();
				currentSpring->assignPoints(A, B, distance);

				if (i != rows - 1)
				{
					m_springs.push_back(std::make_unique<Spring>());
					currentSpring = m_springs[m_springs.size() - 1].get();
					B = m_points[(i + 1) * cols + j + 1].get();
					currentSpring->assignPoints(A, B, distance);
					currentSpring->setType(SpringType::DIAGONAL);
				}
				
			}
		
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

ClothPoint * Cloth::getClothpointAtIndex(int i)
{
	return m_points[i].get();
}

void Cloth::setPosition(Vector3 pos)
{
	m_position = pos;

	for (int i = 0; i < m_points.size(); i++)
	{
		m_points[i]->setPosition(m_points[i]->getPosition() + m_position);

		
	}
}

void Cloth::selfCollision(float dt)
{

	for (int i = 0; i < m_triangles.size(); i++)
	{
		for (int j = i + 1; j < m_triangles.size(); j++)
		{
			if (CollisionUtilities::IntersectTriangles(m_triangles[i].get(), m_triangles[j].get()))
			{

				//add force yo
			}
		}
	}
}
