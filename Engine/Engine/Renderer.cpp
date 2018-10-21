#include "Renderer.h"



Renderer::Renderer()
{
	
}


Renderer::~Renderer()
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

	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = nullptr;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}

	if (m_vertexLayout)
	{
		m_vertexLayout->Release();
		m_vertexLayout = nullptr;
	}

	if (m_depthStencil)
	{
		m_depthStencil->Release();
		m_depthStencil = nullptr;
	}


	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}
	
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


	
	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = 800;
	descDepth.Height = 600;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_device->CreateTexture2D(&descDepth, NULL, &m_depthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
	if (FAILED(hr))
		return hr;


	m_context->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

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
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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


	// Set primitive topology
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	//bind shaders
	m_context->VSSetShader(m_vertexShader, NULL, 0);
	m_context->PSSetShader(m_pixelShader, NULL, 0);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(MatrixBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	if (FAILED(m_device->CreateBuffer(&bd, NULL, &m_matrixBuffer)))
		return hr;

	// Initialize the world matrix
	m_world = DirectX::XMMatrixIdentity();

	// Initialize the projection matrix
	m_projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, 800 / (FLOAT)600, 0.01f, 100.0f); //800 and 600 are window size

	
}

void Renderer::Clear()
{
	
	
	
	
}

void Renderer::Render()
{
		//swap buffers/show back buffer
		m_swapChain->Present(0, 0);
}

void Renderer::Tick()
{
	
	

	//clear back buffer 
	float ClearColor[4] = { 0.0f, 0.125f, 0.6f, 1.0f }; // RGBA
	m_context->ClearRenderTargetView(m_renderTargetView, ClearColor);

	m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::updateViewMatrix(DirectX::XMMATRIX view)
{
	m_view = view;
}



Model * Renderer::createRawModel(Vertex vertices[], int vertexNum, WORD indices[], int indexNum)
{
	Model* model = new Model();

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexNum ;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	if (FAILED(m_device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
		return FALSE;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indexNum;        
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = indices;
	if (FAILED(m_device->CreateBuffer(&bd, &InitData, &indexBuffer)))
		return FALSE;

	model->Init(vertexBuffer, vertexNum, indexBuffer,indexNum);

	return model;
}

void Renderer::renderModel(Model* model)
{
	ID3D11Buffer* vertexBuffer = model->getVertexBuffer();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//create the matrix from all info the model has
	//could also do this in the model itself
	DirectX::XMFLOAT3 pos = model->getPosition();
	DirectX::XMFLOAT3 rot = model->getRotation();
	DirectX::XMFLOAT3 scale = model->getScale();

	DirectX::XMMATRIX mSpin = DirectX::XMMatrixRotationRollPitchYaw(rot.x,rot.y, rot.z);
	DirectX::XMMATRIX mTranslate = DirectX::XMMatrixTranslation(pos.x, pos.y,pos.z);
	DirectX::XMMATRIX mScale = DirectX::XMMatrixScaling(scale.x,scale.y, scale.z);
	DirectX::XMMATRIX modelMatrix = mScale * mSpin * mTranslate;


	//float f = DirectX::XMVectorGetX(modelMatrix.r[0]);
	//update our constant buffers
	MatrixBuffer cb;
	cb.mWorld = DirectX::XMMatrixTranspose(modelMatrix);
	cb.mView = DirectX::XMMatrixTranspose(m_view);
	cb.mProjection = DirectX::XMMatrixTranspose(m_projection);
	m_context->UpdateSubresource(m_matrixBuffer, 0, NULL, &cb, 0, 0);

	//set buffers to the ones of this specific object
	m_context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
	m_context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	m_context->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
	
	//render
	m_context->DrawIndexed(36, 0, 0);
	
}
