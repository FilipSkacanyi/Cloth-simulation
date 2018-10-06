#pragma once


#include "Windows.h"
#include <d3dcompiler.h>
#include "Model.h"
#include "Camera.h"

#pragma comment (lib, "d3dcompiler.lib")

struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
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

	Model* createRawModel(Vertex vertices[], int vertexNum, WORD indices[], int indexNum);

	void renderModel(Model* model);
	

private :

	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_context = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;


	ID3D11VertexShader*     m_vertexShader = nullptr;
	ID3D11PixelShader*      m_pixelShader = nullptr;

	ID3D11InputLayout*  m_vertexLayout = nullptr;

	D3D_FEATURE_LEVEL selectedFeatureLevel;
	
	ID3D11Buffer* m_constantBuffer = nullptr;
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;



	Camera* m_camera = nullptr;
	Model* model = nullptr;
};

