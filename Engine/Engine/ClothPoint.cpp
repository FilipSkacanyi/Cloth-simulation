#include "ClothPoint.h"
#include "Cloth.h"


ClothPoint::ClothPoint()
{
}


ClothPoint::~ClothPoint()
{
}

void ClothPoint::Tick(float dt)
{
	//gravity
	AddForce(Vector3(0, -1, 0) * (m_mass*9.80) * dt * m_gravity);

	if (m_isKinematic)
	{
		m_velocity = Vector3(0, 0, 0);
	}
	else
	{
		//velocity
		m_position = DirectX::XMFLOAT3(m_position.x + dt * m_velocity.x, m_position.y + dt * 1 * m_velocity.y, m_position.z + dt * m_velocity.z);

		AddForce(Vector3(-m_velocity.x * 0.9 * dt, -m_velocity.y * 0.9 * dt, -m_velocity.z * 0.9 * dt));
	}
	

}

