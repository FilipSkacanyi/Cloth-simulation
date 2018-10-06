#include "Camera.h"



Camera::Camera()
{
	m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = DirectX::XMFLOAT3(0.0f,0.0f, 0.0f);
}


Camera::~Camera()
{
}

void Camera::Tick()
{
	DirectX::XMMATRIX rotationMatrix;

	DirectX::XMVECTOR camPosition = DirectX::XMVectorSet(m_position.x, m_position.y, m_position.z, 0.0f);;
	DirectX::XMVECTOR camTarget;
	DirectX::XMVECTOR camUp;

	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR DefaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR camForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR camRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	DirectX::XMMATRIX camRotationMatrix;
	DirectX::XMMATRIX groundWorld;

	float camYaw = m_rotation.x*0.0174532925f; //radians
	float camPitch = m_rotation.y*0.0174532925f; //radians

	camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = DirectX::XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = DirectX::XMVector3Normalize(camTarget);


	camRight = DirectX::XMVector3TransformCoord(DefaultRight, camRotationMatrix);
	camForward = DirectX::XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camUp = DirectX::XMVector3Cross(camForward, camRight);

	camTarget = DirectX::XMVectorAdd(camPosition , camTarget);

	m_viewMatrix = DirectX::XMMatrixLookAtLH(camPosition, camTarget, camUp);

}

void Camera::setPosition(float x, float y, float z)
{
	m_position = DirectX::XMFLOAT3(x, y, z);
}

void Camera::setRotation(float x, float y, float z)
{
	m_rotation = DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMFLOAT3 Camera::getPosition()
{
	return m_position;
}

DirectX::XMFLOAT3 Camera::getRotation()
{
	return m_rotation;
}
void Camera::getViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
