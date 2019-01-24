#pragma once
#include <vector>
#include "Vector3.h"

class ClothPoint;

class ClothTriangle
{
public:
	ClothTriangle();
	~ClothTriangle();

	void addPoints(ClothPoint* a, ClothPoint* b, ClothPoint*c);
	ClothPoint* getClothPointAtIndex(int i);

	void AddForce(Vector3 force);
private:
	
	std::vector<ClothPoint*> m_points;

};

