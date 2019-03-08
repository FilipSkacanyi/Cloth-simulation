#pragma once
#include <vector>
#include "Object.h"


class ClothPoint;

class ClothTriangle : public Object
{
public:
	ClothTriangle();
	~ClothTriangle();

	void addPoints(ClothPoint* a, ClothPoint* b, ClothPoint*c);
	ClothPoint* getClothPointAtIndex(int i);
	void Tick(float dt) override;
	bool Init(Renderer* renderer);
	void Render(Renderer* renderer) override;
	void AddForce(Vector3 force);

	void collision(GameObject* other) override;

	Vector3 getPosition() override;
private:
	
	std::vector<ClothPoint*> m_points;
	

};

