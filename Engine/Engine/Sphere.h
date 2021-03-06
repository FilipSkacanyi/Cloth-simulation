#pragma once
#include "Object.h"
class Sphere :
	public Object
{
public:
	Sphere();
	~Sphere();

	void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color, std::wstring texturefile) override;
	void Tick(float dt) override;
};

