#pragma once


#include <memory>
#include "Scene.h"


class Application
{
public:
	Application();
	~Application();

	bool Init();
	void Run();
		

private:
	bool Tick();
	void Render();
	bool InitWindow();


	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	std::unique_ptr<Renderer> m_renderer = nullptr;

	Scene* m_scene = nullptr;
};

