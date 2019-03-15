#pragma once
#include <vector>
#include "Object.h"


class ClothPoint;
class Texture;

class ClothTriangle : public Object
{
public:
	ClothTriangle();
	~ClothTriangle();

	void addPoints(ClothPoint* a, ClothPoint* b, ClothPoint*c);
	void setTextureCoords(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b, DirectX::XMFLOAT2 c);

	
	ClothPoint* getClothPointAtIndex(int i);
	void Tick(float dt) override;
	bool Init(Renderer* renderer, Texture* texture);
	void Render(Renderer* renderer) override;
	void recalculateVertices(Renderer* renderer);

	Vector3 getSurfaceNormal();
	void AddForce(Vector3 force);

	void collision(GameObject* other) override;

	Vector3 getPosition() override;
private:
	
	std::vector<ClothPoint*> m_points;
	std::vector<DirectX::XMFLOAT2> m_texturecoords;

};

