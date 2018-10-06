#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

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

	bool Init(ID3D11Buffer* vertexBuffer, int vertexNum, ID3D11Buffer* indexBuffer);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
	int getVertexNumber(); 
private:

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;


	int m_vertexNumber = 0;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};

