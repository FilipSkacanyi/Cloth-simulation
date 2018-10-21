#include "Object.h"



Object::Object()
{
	m_position = DirectX::XMFLOAT3(0, 0, 0);
	m_rotation = DirectX::XMFLOAT3(0, 0, 0);
	m_scale = DirectX::XMFLOAT3(1, 1, 1);
}


Object::~Object()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
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
				vertices[iv].position = DirectX::XMFLOAT3(x, y, -z);
				vertices[iv].color = DirectX::XMFLOAT4(rand() % 2,rand() % 2,rand() % 2, 1.0f);
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

				indices[ii++] = ind3 - 1;
				indices[ii++] = ind2 - 1;
				indices[ii++] = ind1 - 1;
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

	

}


void Object::Tick(double dt)
{ 
	//m_rotation.y += 3 * dt;
	m_elapsed_time += dt;

	m_position = DirectX::XMFLOAT3(m_position.x + dt * m_velocity.x, m_position.y + dt*1* m_velocity.y, m_position.z + dt* m_velocity.z);
	
	if (m_elapsed_time > 0.3)
	{
		m_elapsed_time = 0;
		//velocity decay / air ressistance
		m_velocity = DirectX::XMFLOAT3(m_velocity.x* 0.9, m_velocity.y*0.9, m_velocity.z*0.9);
	}

	//gravity
	m_velocity = DirectX::XMFLOAT3(m_velocity.x, m_velocity.y + (-(dt * m_mass*9.80) * m_gravity), m_velocity.z);

	if (m_position.y < -3)
	{
		//reset velocity
		//m_velocity = DirectX::XMFLOAT3(0, 0, 0);
		//m_position.y = 0;
		//m_velocity = DirectX::XMFLOAT3(-m_velocity.x , -m_velocity.y,- m_velocity.z);
		//AddForce(DirectX::XMFLOAT3(-m_velocity.x, -m_velocity.y, -m_velocity.z));

		AddForce(DirectX::XMFLOAT3(0, 5, 0));
	}
	if (m_position.x < -5 )
	{
		//reset velocity
		//m_velocity = DirectX::XMFLOAT3(0, 0, 0);
		//m_position.y = 0;
		//m_velocity =
		AddForce(DirectX::XMFLOAT3(5, 0, 0));
			
	}
	if (m_position.x > 5)
	{
		AddForce(DirectX::XMFLOAT3(-5, 0, 0));
	}

	if (m_position.z < -2)
	{
		//reset velocity
		//m_velocity = DirectX::XMFLOAT3(0, 0, 0);
		//m_position.y = 0;
		//m_velocity =
		AddForce(DirectX::XMFLOAT3(0, 0, 2));

	}
	if (m_position.z > 2)
	{
		AddForce(DirectX::XMFLOAT3(0, 0, -2));
	}


	m_model->setPosition(m_position);
	m_model->setRotation(m_rotation);
	m_model->setScale(m_scale);

	

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

void Object::resetVelocity(VelocityAxis axis)
{
	switch (axis)
	{
	case VelocityAxis::X_AXIS:
	{
		
		break;
	}
	case VelocityAxis::Y_AXIS:
	{
		break;
	}
	case VelocityAxis::Z_AXIS:
	{
		break;
	}
	case VelocityAxis::ALL_AXIS:
	{
		m_velocity = DirectX::XMFLOAT3(0, 0, 0);
		break;
	}

	}
}

void Object::AddForce(DirectX::XMFLOAT3 force)
{
	m_velocity = DirectX::XMFLOAT3(m_velocity.x + force.x, m_velocity.y +  force.y, m_velocity.z + force.z);
}

void Object::collision(Object * other)
{
	//m_velocity = DirectX::XMFLOAT3(-m_velocity.x, -m_velocity.y, -m_velocity.z);
	DirectX::XMFLOAT3 dir;
	dir = DirectX::XMFLOAT3((other->getPosition().x - m_position.x) ,( other->getPosition().y - m_position.y) , (other->getPosition().z - m_position.z) );
	other->AddForce(dir);
}

float Object::getMass()
{
	return 0.0f;
}

void Object::setGravity(float grav)
{
	m_gravity = grav;
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

Collider * Object::getCollider()
{
	return m_collider;
}
