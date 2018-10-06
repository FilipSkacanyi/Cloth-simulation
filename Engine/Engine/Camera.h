#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	~Camera();

	void Tick();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();

	void getViewMatrix(DirectX::XMMATRIX& viewMatrix);

private:

	DirectX::XMFLOAT3 m_position, m_rotation;
	DirectX::XMMATRIX m_viewMatrix;
};

