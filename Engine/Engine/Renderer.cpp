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

	if (m_WireFrame)
	{
		m_WireFrame->Release();
		m_WireFrame = nullptr;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = nullptr;

	}
	
}

bool Renderer::Init(HWND hwnd)
{
	//create the swapchain
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
	hr = D3DCompileFromFile(L"./Shaders/vertexshader.vs", nullptr, nullptr, "VS", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_vertexShaderBlob, &errorBlob);
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
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
	hr = D3DCompileFromFile(L"./Shaders/pixelshader.ps", nullptr, nullptr, "PS", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_pixelShaderBlob, &errorBlob);
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

	
	//create the rasterizer states
	//for different types of rendering
	D3D11_RASTERIZER_DESC wfdesc;
	ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
	wfdesc.FillMode = D3D11_FILL_WIREFRAME;
	wfdesc.CullMode = D3D11_CULL_NONE;
	hr = m_device->CreateRasterizerState(&wfdesc, &m_WireFrame);
	
	wfdesc.FillMode = D3D11_FILL_SOLID;
	hr = m_device->CreateRasterizerState(&wfdesc, &m_Solid);

	wfdesc.CullMode = D3D11_CULL_BACK;
	hr = m_device->CreateRasterizerState(&wfdesc, &m_backface);

	wfdesc.CullMode = D3D11_CULL_FRONT;
	hr = m_device->CreateRasterizerState(&wfdesc, &m_frontface);
	//set the defoault rasterizer state
	m_context->RSSetState(m_Solid);

	D3D11_BUFFER_DESC lightBufferDesc;

	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	hr = m_device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(hr))
	{
		return false;
	}



	// Create the light object.
	m_Light = new Light();
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->setDirection(0.0f, 0.0f, 1.0f);
	m_Light->setAmbientColor(0.3f, 0.3f, 0.3f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// Lock the light constant buffer so it can be written to.
	hr = m_context->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr))
	{
		return false;
	}

	LightBuffer* dataPtr = nullptr;
	// Get a pointer to the data in the constant buffer.
	dataPtr = (LightBuffer*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr->diffuseColor = m_Light->GetDiffuseColor();
	dataPtr->lightDirection = m_Light->GetDirection();
	dataPtr->ambientColor = m_Light->GetAmbientColor();
	dataPtr->padding = 0.0f;

	// Unlock the constant buffer.
	m_context->Unmap(m_lightBuffer, 0);

	m_context->PSSetConstantBuffers(0, 1, &m_lightBuffer);



	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	hr = m_device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(hr))
	{
		return false;
	}





	return true;
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



Model * Renderer::createRawModel(Vertex vertices[], int vertexNum, unsigned long indices[], int indexNum)
{
	//this function takes in the vertex and index buffer and returns a pointer to a model
	//this model can then be rendered by calling RenderModel() function
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
	bd.ByteWidth = sizeof(unsigned long) * indexNum;        
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
	Vector3 pos = model->getPosition();
	Vector3 rot = model->getRotation();
	Vector3 scale = model->getScale();

	float rad = 0.0174533;

	DirectX::XMMATRIX mSpin = DirectX::XMMatrixRotationRollPitchYaw(rot.x* rad,rot.y * rad, rot.z *rad);
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


	// Set shader texture resource in the pixel shader.
	ID3D11ShaderResourceView* texture = model->getTexture();
	m_context->PSSetShaderResources(0, 1, &texture);
	m_context->PSSetSamplers(0, 1, &m_sampleState);

	//set buffers to the ones of this specific object
	
	m_context->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
	m_context->PSSetConstantBuffers(0, 1, &m_lightBuffer);
	m_context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	m_context->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	
	//render
	m_context->DrawIndexed(model->getIndexCount(), 0, 0);
	
}

void Renderer::backfaceCull()
{
	m_context->RSSetState(m_backface);
}

void Renderer::frontfaceCull()
{
	m_context->RSSetState(m_frontface);
}

void Renderer::WireframeRendering()
{
	m_context->RSSetState(m_WireFrame);
}

void Renderer::SolidRendering()
{
	m_context->RSSetState(m_Solid);
}
