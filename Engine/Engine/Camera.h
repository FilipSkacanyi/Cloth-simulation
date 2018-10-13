#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	~Camera();

	void Tick();

	void setPosition(float x, float y, float z);
	void setPosition(DirectX::XMFLOAT3 pos);
	void setRotation(float x, float y, float z);
	void setRotation(DirectX::XMFLOAT3 rot);

	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();

	void getViewMatrix(DirectX::XMMATRIX& viewMatrix);

	DirectX::XMFLOAT3 getForward();

private:
	DirectX::XMFLOAT3 m_cameraForward;
	DirectX::XMFLOAT3 m_position, m_rotation;
	DirectX::XMMATRIX m_viewMatrix;
};

