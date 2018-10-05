#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = nullptr;
}

bool Application::Init()
{
	if (!InitWindow())
	{
		return false;
	}

	m_renderer = std::make_unique<Renderer>();
	m_renderer->Init(m_hwnd);


	// Create vertex buffer
	Vertex vertices[] =
	{
		DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(0.0f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(-1.0f, -0.5f, 0.5f),
	};

	Vertex vertices1[] =
	{
		DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f),
		DirectX::XMFLOAT3(1.0f, -0.5f, 0.5f),
		DirectX::XMFLOAT3(0.0f, -0.5f, 0.5f),
	};


	

	model = m_renderer->createRawModel(vertices, 3);

	model1 = m_renderer->createRawModel(vertices1, 3);

	return true;
}

void Application::Run()
{

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Tick();
			
		}
		
	}
}

bool Application::Tick()
{
	m_renderer->Clear();
	
	m_renderer->renderModel(model);
	m_renderer->renderModel(model1);

	m_renderer->Render();
	return false;
}

bool Application::InitWindow()
{
	WNDCLASSEX wcex;

	//get instance of this app
	m_hInstance = GetModuleHandle(NULL);
	m_applicationName = "Engine";

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbWndExtra = 0; //alocating of extra bytes
	wcex.cbClsExtra = 0; // currently we dont want any
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(m_hInstance, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(BACKGROUND_BLUE);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_applicationName;
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	RECT rc = { 0,0,800,600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	m_hwnd = CreateWindow(m_applicationName, "Collision detection",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX, //style
		CW_USEDEFAULT, CW_USEDEFAULT, //position
		rc.right -rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);

	if (!m_hwnd)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOW);

	return true;
}

LRESULT Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
	{
		//PostQuitMessage(0);
		PostMessage(hWnd, WM_QUIT, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

