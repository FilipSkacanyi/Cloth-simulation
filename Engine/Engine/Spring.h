#pragma once
class GameObject;

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
	void assignPoints(GameObject* pointA, GameObject* pointB, float offset_distance);
	void setType(SpringType type) { m_type = type; }

private:
	GameObject* m_point_A = nullptr;
	GameObject* m_point_B = nullptr;

	SpringType m_type = SpringType::STRAIT;

	float m_stiffness = 0.5;
	float m_offset_distance = 1;

	float m_max_stretch = 1000;
};

