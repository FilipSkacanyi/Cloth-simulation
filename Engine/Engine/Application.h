#pragma once

#include "Windows.h"
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib" )


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


};

