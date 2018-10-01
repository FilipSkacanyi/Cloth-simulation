#pragma once
#include <Windows.h>

#include "Direct3D.h"


// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();


	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Tick();

private:
	bool Render();

private:

	Direct3D* m_D3D = nullptr;
};

