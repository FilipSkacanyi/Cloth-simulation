#pragma once


#include "Windows.h"
#include <d3dcompiler.h>
#include "Model.h"

#pragma comment (lib, "d3dcompiler.lib")


class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init(HWND hwnd);

	void Draw();
	void Render();

	Model* createRawModel();

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
	
};

