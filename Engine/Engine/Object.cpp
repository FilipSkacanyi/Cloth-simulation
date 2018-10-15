#include "Object.h"



Object::Object()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Object::~Object()
{
	if (m_boundingBox)
	{
		delete m_boundingBox;
		m_boundingBox = nullptr;
	}

	if (m_model)
	{
		delete m_model;
		m_model = nullptr;
	}
}

void Object::Init(Renderer * renderer, std::string fileName, DirectX::XMFLOAT4 color)
{
	//Vertex vertices[] =
	//{
	//	{ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
	//	{ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	//};

	//// Create index buffer
	//WORD indices[] =
	//{
	//	3,1,0,
	//	2,1,3,

	//	0,5,4,
	//	1,5,0,

	//	3,4,7,
	//	0,4,3,

	//	1,6,5,
	//	2,6,1,

	//	2,7,6,
	//	3,7,2,

	//	6,4,5,
	//	7,4,6,
	//};

	/*std::ifstream objectfile;
	objectfile.open(fileName);
	int vcount = 0;
	int icount = 0;

	objectfile >> vcount;
	Vertex* vertices = new Vertex[vcount];
	for (int i = 0; i < vcount; i++)
	{
		float x = 0;
		float y = 0;
		float z = 0;
		objectfile >> x;
		objectfile >> y;
		objectfile >> z;
		vertices[i].position = DirectX::XMFLOAT3(x, y, z);
		vertices[i].color = color;
	}
	objectfile >> icount;
	WORD* indices = new WORD[icount];
	for (int i = 0; i < icount; i++)
	{
		int j;
		objectfile >> j;
		indices[i] = j;
	}
	objectfile.close();
	m_model = renderer->createRawModel(vertices, vcount, indices, icount);

	delete[] vertices;
	delete[] indices;*/

	std::ifstream objectfile, fileCounts;
	int vcount = 0;
	int icount = 0;
	fileCounts.open(fileName);
	char input;

	fileCounts.get(input);

	int i = 0;
	while (!fileCounts.eof())
	{
		if (input == 'v')
		{
			fileCounts.get(input);
			if (input == ' ')
			{
				vcount++;
			}
		}

		if (input == 'f')
		{
			fileCounts.get(input);
			if (input == ' ')
			{
				icount += 3; //each face is a triangle
			}
		}

		fileCounts.get(input);
		i++;
		if (i > 1000000)
		{
			assert(false);
		}
	}

	fileCounts.close();

	objectfile.open(fileName);

	Vertex* vertices = new Vertex[vcount];
	WORD* indices = new WORD[icount];

	/*Vertex vertices[8];
	WORD indices[36];*/
	int iv = 0;
	int ii = 0;
	int fail = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	int ind1, ind2, ind3;

	objectfile.get(input);
	while (!objectfile.eof())
	{
		if (input == 'v')
		{
			objectfile.get(input);
			if (input == ' ')
			{

				objectfile >> x;
				objectfile >> y;
				objectfile >> z;
				vertices[iv].position = DirectX::XMFLOAT3(x, y, z);
				vertices[iv].color = color;
				iv++;
			}
		}

		if (input == 'f')
		{
			objectfile.get(input);
			if (input == ' ')
			{
				char garbage = 0;
				int skip = 0;

				objectfile >> ind1 >> garbage >> skip >> garbage >> skip;
				objectfile >> ind2 >> garbage >> skip >> garbage >> skip;
				objectfile >> ind3 >> garbage >> skip >> garbage >> skip;

				indices[ii++] = ind1 - 1;
				indices[ii++] = ind2 - 1;
				indices[ii++] = ind3 - 1;
			}
		}
		objectfile.get(input);
		fail++;
		if (fail > 1000000)
		{
			assert(false);
		}
	}

	objectfile.close();
	m_model = renderer->createRawModel(vertices, vcount, indices, icount);

	delete[] vertices;
	delete[] indices;

	

	//create bounding box
	m_boundingBox = new DirectX::BoundingOrientedBox();
	//init bounding box
	m_boundingBox->Center = m_position;
	m_boundingBox->Extents = m_scale;
	DirectX::XMStoreFloat4(&m_boundingBox->Orientation, DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z));
	
}

void Object::objFile(std::string fileName)
{
	std::ifstream objectfile, fileCounts;
	int vcount = 0;
	int icount = 0;
	fileCounts.open(fileName);
	char input;
	fileCounts.get(input);
	while (!fileCounts.eof())
	{
		if (input == 'v')
		{
			fileCounts.get(input);
			if (input == ' ')
			{
				vcount++;
			}
		}
		
		if (input == 'f')
		{
			fileCounts.get(input);
			if (input == ' ')
			{
				icount += 3; //each face is a triangle
			} 
		}
	}

	fileCounts.close();



	objectfile.open(fileName);
	
	Vertex* vertices = new Vertex[vcount];
	WORD* indices = new WORD[icount];
	int iterator = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	int ind1, ind2, ind3;

	objectfile.get(input);
	while (!objectfile.eof())
	{
		if (input == 'v')
		{
			objectfile.get(input);
			if (input == ' ')
			{
				
				objectfile >> x;
				objectfile >> y;
				objectfile >> z;
				vertices[iterator].position = DirectX::XMFLOAT3(x, y, z);
			}
		}

		if (input == 'f')
		{
			char garbage = 0;
			int skip = 0;

			objectfile >> ind1 >> garbage >> garbage >> skip;
			objectfile >> ind2 >> garbage >> garbage >> skip;
			objectfile >> ind3 >> garbage >> garbage >> skip;

			indices[iterator] = ind1;
			indices[iterator + 1] = ind2;
			indices[iterator + 2] = ind3;

		}

		iterator++;
	}
	
	objectfile.close();
	//m_model = renderer->createRawModel(vertices, vcount, indices, icount);

	delete[] vertices;
	delete[] indices;
}

void Object::Tick(double dt)
{
	m_rotation.y += 100*dt;

	m_model->setPosition(m_position);
	m_model->setRotation(m_rotation);
	m_model->setScale(m_scale);

	//update bounding box
	m_boundingBox->Center = m_position;
	m_boundingBox->Extents = m_scale;
	DirectX::XMStoreFloat4(&m_boundingBox->Orientation, DirectX::XMQuaternionRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z));
}

void Object::Render(Renderer * renderer)
{
	renderer->renderModel(m_model);
}

void Object::setPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
}

void Object::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}

void Object::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void Object::setRotation(DirectX::XMFLOAT3 rot)
{
	m_rotation = rot;
}

void Object::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

void Object::setScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

DirectX::XMFLOAT3 Object::getPosition()
{
	return m_position;
}

DirectX::XMFLOAT3 Object::getRotation()
{
	return m_rotation;
}

DirectX::XMFLOAT3 Object::getScale()
{
	return m_scale;
}

DirectX::BoundingOrientedBox * Object::getBoundingBox()
{
	return m_boundingBox;
}