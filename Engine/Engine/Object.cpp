#include "Object.h"
#include "OBJ_Loader.h"



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
	

	objl::Loader loader;
	loader.LoadFile(fileName);

	//go trough the loaded data and translate it to my dat types;
	
	int vertcount = loader.LoadedVertices.size();
	int indcount = loader.LoadedIndices.size();
	Vertex* vertices1 = new Vertex[vertcount];
	WORD* indices1 = new WORD[indcount];

	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		//loader.LoadedVertices[i].Position;
		vertices1[i].position = DirectX::XMFLOAT3(loader.LoadedVertices[i].Position.X, 
												loader.LoadedVertices[i].Position.Y,
												loader.LoadedVertices[i].Position.Z);
		vertices1[i].color = DirectX::XMFLOAT4(rand() % 2, rand() % 2, rand() % 2, 1.0f);
	}
	
	for (int i = 0; i < loader.LoadedIndices.size(); i++)
	{
		indices1[i] = loader.LoadedIndices[i];
	}

	
	m_model = renderer->createRawModel(vertices1, vertcount, indices1, indcount);

	
	delete[] vertices1;
	delete[] indices1;

	

}


void Object::Tick(double dt)
{ 
	//m_rotation.y += 3 * dt;
	if (m_kinematic)
	{
		resetVelocity(ALL_AXIS);
	}

	m_elapsed_time += dt;

	m_position = DirectX::XMFLOAT3(m_position.x + dt * m_velocity.x, m_position.y + dt*1* m_velocity.y, m_position.z + dt* m_velocity.z);
	
	//velocity decay / air ressistance
	AddForce(DirectX::XMFLOAT3(-m_velocity.x * 1 * dt, -m_velocity.y * 1 * dt, -m_velocity.z* 1 * dt));
	

	//gravity
	m_velocity = DirectX::XMFLOAT3(m_velocity.x, m_velocity.y + (-(dt * m_mass*9.80) * m_gravity), m_velocity.z);

	
	


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
	AddForce(DirectX::XMFLOAT3(-m_velocity.x * (1+m_bounciness), -m_velocity.y * (1 + m_bounciness), -m_velocity.z* (1 + m_bounciness)) );
	/*DirectX::XMFLOAT3 dir;
	dir = DirectX::XMFLOAT3((other->getPosition().x - m_position.x) ,( other->getPosition().y - m_position.y) , (other->getPosition().z - m_position.z) );
	other->AddForce(dir);*/

	//other->AddForce(m_velocity);

	//Vector3 normal = Vector3(m_position.x - other->getPosition().x, m_position.y - other->getPosition().y, m_position.z - other->getPosition().z);
	//normal.Normalize();
	//float mag = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y + m_velocity.z * m_velocity.z);

	////normal = normal * mag;
	//normal = normal * m_bounciness;

	//DirectX::XMFLOAT3 v = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
	//AddForce(v);
}

float Object::getMass()
{
	return m_mass;
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
