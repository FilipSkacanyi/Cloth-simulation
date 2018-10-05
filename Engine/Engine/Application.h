#pragma once

#include "Renderer.h"
#include <memory>

class Application
{
public:
	Application();
	~Application();

	bool Init();
	void Run();
		

private:
	bool Tick();
	bool InitWindow();


	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	std::unique_ptr<Renderer> m_renderer = nullptr;

	Model* model = nullptr;
	Model* model1 = nullptr;
};

