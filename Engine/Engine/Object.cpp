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
	unsigned long* indices1 = new unsigned long[indcount];

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
	

	if (m_isKinematic)
	{
		m_velocity = Vector3(0, 0, 0);
	}
	else
	{
		//gravity
		AddForce(Vector3(0, -9.80 * m_mass, 0) * dt * m_gravity);
		//AddForce(m_acceleration * (-1) * (m_velocity.Magnitude() * m_velocity.Magnitude()));

		//force = mass * acceleration;
		//acceleration = force / mass
		m_acceleration = m_force / m_mass;

		//velocity
		m_velocity = m_velocity + m_acceleration * dt;
		//m_velocity = m_force;
		m_position = m_position + (m_velocity * dt);

		m_velocity = m_velocity - m_velocity * 0.95 *dt;
		//air ressistance

		m_force = Vector3(0, 0, 0);


	}

	m_collider->setPosition(m_position);
	

	if (m_model)
	{
		m_model->setPosition(m_position);
		m_model->setRotation(m_rotation);
		m_model->setScale(m_scale);
	}

}

void Object::Render(Renderer * renderer)
{
	if (m_model)
	{
		renderer->renderModel(m_model);
	}
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



float Object::getMass()
{
	return m_mass;
}

void Object::setGravity(float grav)
{
	m_gravity = grav;
}


void Object::AddForce(Vector3 force)
{
	m_force = m_force + force;
}

void Object::collision(GameObject * other)
{
	//other->AddForce(Vector3(-m_velocity.x * (1  ), -m_velocity.y * (1 ), -m_velocity.z* (1 )/1000));
	Vector3 dir;
	dir = DirectX::XMFLOAT3((other->getPosition().x - m_position.x), (other->getPosition().y - m_position.y), (other->getPosition().z - m_position.z));
	//other->AddForce(dir / 10);

	//other->AddForce(m_velocity);

	//Vector3 normal = Vector3(m_position.x - other->getPosition().x, m_position.y - other->getPosition().y, m_position.z - other->getPosition().z);
	//normal.Normalize();
	//float mag = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y + m_velocity.z * m_velocity.z);

	////normal = normal * mag;
	//normal = normal * m_bounciness;

	//DirectX::XMFLOAT3 v = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
	//AddForce(v);
}




