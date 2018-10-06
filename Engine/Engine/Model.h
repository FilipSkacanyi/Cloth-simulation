#pragma once

#include <DirectXMath.h>
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

	bool Init(ID3D11Buffer* vertexBuffer, int vertexNum, ID3D11Buffer* indexBuffer);

	void Tick();
	//void Render(Renderer* renderer);

	ID3D11Buffer* getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
	int getVertexNumber(); 


	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

private:



	int m_vertexNumber = 0;
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
};

