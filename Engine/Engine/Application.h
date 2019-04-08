#pragma once


#include <memory>
#include "Scene.h"
#include "Input.h"
#include <chrono>

class Application
{
public:
	Application();
	~Application();

	bool Init();
	void Run();
	
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Tick(float dt);
	void Render();
	bool InitWindow();

	std::chrono::duration<float> m_delta_time;
	float m_frame_rate_cap = 10000.0f;
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	std::unique_ptr<Renderer> m_renderer = nullptr;

	Scene* m_scene = nullptr;
	Input * m_input = nullptr;


};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Application* ApplicationHandle = nullptr;

