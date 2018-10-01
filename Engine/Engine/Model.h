#pragma once

#include <d3d11.h>
#include <DirectXMath.h>


class Model
{
private:
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;

	};

	
public:
	Model();
	~Model();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer = nullptr, *m_indexBuffer = nullptr;
	int m_vertexCount, m_indexCount;
};

