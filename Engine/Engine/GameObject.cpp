#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Tick(float dt)
{
}

DirectX::XMFLOAT3 GameObject::getPosition()
{
	return m_position;
}

void GameObject::setPosition(DirectX::XMFLOAT3 pos)
{
	m_position = pos;
}

void GameObject::AddForce(Vector3 force)
{
	m_velocity = m_velocity + force;
}


void GameObject::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setRotation(DirectX::XMFLOAT3 rot)
{
	m_rotation = rot;
}

void GameObject::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

float GameObject::getMass()
{
	return m_mass;
}

void GameObject::setGravity(float grav)
{
	m_gravity = grav;
}

DirectX::XMFLOAT3 GameObject::getRotation()
{
	return m_rotation;
}

DirectX::XMFLOAT3 GameObject::getScale()
{
	return m_scale;
}