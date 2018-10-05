#include "Renderer.h"



Renderer::Renderer()
{
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;

	}

	if (m_context)
	{
		m_context->Release();
		m_context = nullptr;
	}
}


Renderer::~Renderer()
{
}

bool Renderer::Init(HWND hwnd)
{

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,

	};

	

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels, ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION, &sd,&m_swapChain, &m_device, &selectedFeatureLevel, &m_context)))
	{
		return false;
	}


	// Create a render target view
	ID3D11Texture2D *pBackBuffer;
	if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return FALSE;
	HRESULT hr = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return FALSE;
	m_context->OMSetRenderTargets(1, &m_renderTargetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = 800;  //temprorary values
	vp.Height = 600; //temporary values
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_context->RSSetViewports(1, &vp);

	ID3DBlob* errorBlob = nullptr;

	ID3DBlob* m_pixelShaderBlob = nullptr;
	ID3DBlob* m_vertexShaderBlob = nullptr;

	 hr = S_OK;

	 //compile vertexshader from a file
	hr = D3DCompileFromFile(L"shaders.fx", nullptr, nullptr, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_vertexShaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			return false;
		}
	}

	//create vertex shader
	if (FAILED(m_device->CreateVertexShader(m_vertexShaderBlob->GetBufferPointer(), m_vertexShaderBlob->GetBufferSize(), nullptr, &m_vertexShader)))
	{
		m_vertexShaderBlob->Release();
		return false;
	}
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	if (FAILED(m_device->CreateInputLayout(layout, numElements, m_vertexShaderBlob->GetBufferPointer(),
		m_vertexShaderBlob->GetBufferSize(), &m_vertexLayout)))
		return FALSE;


	// Set the input layout
	m_context->IASetInputLayout(m_vertexLayout);
	m_vertexShaderBlob->Release();
	
	//compile pixelshader from a file
	hr = D3DCompileFromFile(L"shaders.fx", nullptr, nullptr, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_pixelShaderBlob, &errorBlob);
	if (FAILED(hr))
	{
		OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
		errorBlob->Release();

		return false;
	}

	// Create the pixel shader
	hr = m_device->CreatePixelShader(m_pixelShaderBlob->GetBufferPointer(), m_pixelShaderBlob->GetBufferSize(), nullptr, &m_pixelShader);
	m_pixelShaderBlob->Release();
	if (FAILED(hr))
		return hr;


	Model* model = new Model();



	// Create vertex buffer
	Vertex vertices[] =
	{
		DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f),
	};

	ID3D11Buffer* vertexBuffer = nullptr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	if (FAILED(m_device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
		return FALSE;



	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set primitive topology
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	model->Init(vertexBuffer);

	


	return true;
}

void Renderer::Draw()
{
}

void Renderer::Render()
{

	
		//
		// Clear the backbuffer
		//
		float ClearColor[4] = { 0.0f, 0.125f, 0.6f, 1.0f }; // RGBA
		m_context->ClearRenderTargetView(m_renderTargetView, ClearColor);
		
		// Render a triangle 
		m_context->VSSetShader(m_vertexShader, NULL, 0);
		m_context->PSSetShader(m_pixelShader, NULL, 0);
		m_context->Draw(3, 0);


		m_swapChain->Present(0, 0);
	

}

Model * Renderer::createRawModel()
{
	return nullptr;
}

void Renderer::renderModel(Model * model)
{
	
}
