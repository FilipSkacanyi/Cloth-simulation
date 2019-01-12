#pragma once
class ClothPoint;

enum SpringType
{
	DIAGONAL,
	STRAIT
};

class Spring
{
public:
	Spring();
	~Spring();

	void Tick(float dt);
	void assignPoints(ClothPoint* pointA, ClothPoint* pointB, float offset_distance);
	void setType(SpringType type) { m_type = type; }

private:
	ClothPoint* m_point_A = nullptr;
	ClothPoint* m_point_B = nullptr;

	SpringType m_type = SpringType::STRAIT;

	float m_stiffness = 0.2;
	float m_offset_distance = 1;

	float m_max_stretch = 1.1;
};

