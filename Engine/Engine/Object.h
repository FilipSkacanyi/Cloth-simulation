#pragma once


#include "Renderer.h"
#include <string>
#include <fstream>
class Object
{
public:
	Object();
	~Object();

	void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color);
	void objFile(std::string fileName);
	void Tick(double dt);
	void Render(Renderer* renderer);

	void setPosition(float x, float y, float z);
	void setPosition(DirectX::XMFLOAT3 pos);
	void setRotation(float x, float y, float z);
	void setRotation(DirectX::XMFLOAT3 rot);
	void setScale(float x, float y, float z);
	void setScale(DirectX::XMFLOAT3 scale);


	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMFLOAT3 getScale();

	DirectX::BoundingOrientedBox* getBoundingBox();

private:

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMFLOAT3 m_scale;


	Model* m_model = nullptr;
	DirectX::BoundingOrientedBox* m_boundingBox = nullptr;
};

