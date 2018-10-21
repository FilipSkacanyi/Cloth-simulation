#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
	if (m_scene)
	{
		delete m_scene;
		m_scene = nullptr;
	}
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

	m_scene = new Scene();
	m_scene->Init(m_renderer.get());

	m_input = new Input();
	m_input->init();

	ApplicationHandle = this;
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
			auto start = std::chrono::high_resolution_clock::now();
			Tick(m_delta_time.count());
			Render();
			auto end = std::chrono::high_resolution_clock::now();
			m_delta_time = end - start;

		}
		
	}
}

LRESULT Application::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		m_input->keyDown((unsigned int)wParam);
		m_input->setAction(Action::KEY_PRESSED);
		break;
	}
	case WM_KEYUP:
	{
		m_input->keyUp((unsigned int)wParam);
		m_input->setAction(Action::KEY_RELEASED);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return 0;
}

bool Application::Tick(double dt)
{
	m_renderer->Tick();
	m_scene->input(m_input, dt);
	m_scene->Tick(dt);
	m_input->setAction(Action::NONE);
	return false;
}

void Application::Render()
{
	m_scene->Render();
	//make sure renderer renders last
	m_renderer->Render();
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		return ApplicationHandle->MessageHandler(hWnd,message,wParam,lParam);
	}

	return 0;
}

