#pragma once
#include "Object.h"

class AlignedBoxCollider;

class Cube :
	public Object
{
public:
	Cube();
	~Cube();

	void Init(Renderer* renderer, std::string fileName, DirectX::XMFLOAT4 color);
	void Tick(float dt) override;
private:

};

