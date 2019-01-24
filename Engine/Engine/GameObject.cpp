#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Tick(double dt)
{
	
}

Vector3 GameObject::getPosition()
{
	return m_position;
}

void GameObject::setPosition(Vector3 pos)
{
	m_position = pos;
}

Vector3 GameObject::getRotation()
{
	return m_rotation;
}

Vector3 GameObject::getScale()
{
	return m_scale;
}

void GameObject::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setRotation(Vector3 rot)
{
	m_rotation = rot;
}

void GameObject::setScale(float x, float y, float z)
{
	m_scale = DirectX::XMFLOAT3(x, y, z);
}

void GameObject::setScale(Vector3 scale)
{
	m_scale = scale;
}

Collider * GameObject::getCollider()
{
	return m_collider;
}

void GameObject::collision(GameObject * other)
{
}
