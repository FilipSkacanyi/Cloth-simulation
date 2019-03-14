#pragma once


#include "Windows.h"
#include <d3dcompiler.h>
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "WICTextureLoader.h"

#pragma comment (lib, "d3dcompiler.lib")

struct MatrixBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};

struct LightBuffer
{
	DirectX::XMFLOAT4 diffuseColor;
	DirectX::XMFLOAT3 lightDirection;
	float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init(HWND hwnd);

	void Clear() /* Clear the backbuffer */;
	void Render();
	void Tick();

	void updateViewMatrix(DirectX::XMMATRIX view);

	Model* createRawModel(Vertex vertices[], int vertexNum, unsigned long indices[], int indexNum);

	void renderModel(Model* model);
	
	ID3D11Device* getDevice() { return m_device; }
	ID3D11DeviceContext* getContext() { return m_context; }

private :

	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_context = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11Texture2D * m_depthStencil = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;

	ID3D11VertexShader*     m_vertexShader = nullptr;
	ID3D11PixelShader*      m_pixelShader = nullptr;

	ID3D11Buffer* m_lightBuffer = nullptr;

	ID3D11InputLayout*  m_vertexLayout = nullptr;

	D3D_FEATURE_LEVEL selectedFeatureLevel;
	
	ID3D11Buffer* m_matrixBuffer = nullptr;

	ID3D11RasterizerState* m_WireFrame = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;

	Light* m_Light = nullptr;

	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;

};

