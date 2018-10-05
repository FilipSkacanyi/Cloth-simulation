#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib" )
struct Vertex
{
	DirectX::XMFLOAT3 position;
};

class Model
{
public:
	Model();
	~Model();

	bool Init(ID3D11Buffer* vertexBuffer, int vertexNum);

	ID3D11Buffer* getVertexBuffer();
	int getVertexNumber(); 
private:
	int m_vertexNumber = 0;
	ID3D11Buffer* m_vertexBuffer = nullptr;
};

