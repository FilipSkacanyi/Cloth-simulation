#pragma once

#include "Vector3.h"
#include <DirectXCollision.h>
#include <d3d11.h>
//#include "Renderer.h"

#pragma comment (lib, "d3d11.lib" )
struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

class Model
{
public:
	Model();
	~Model();

	bool Init(ID3D11Buffer* vertexBuffer, int vertexNum, ID3D11Buffer* indexBuffer, int indexNum);

	void Tick();
	//void Render(Renderer* renderer);


	void setPosition(float x, float y, float z);
	void setPosition(Vector3 pos);
	void setRotation(float x, float y, float z);
	void setRotation(Vector3 rot);
	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);

	
	Vector3 getPosition();
	Vector3 getRotation();
	Vector3 getScale();

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
	int getVertexCount(); 
	int getIndexCount();

	


private:
	
	Vector3 m_position;
	Vector3 m_rotation;
	Vector3 m_scale;

	int m_indexCount = 0;
	int m_vertexCount = 0;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};

