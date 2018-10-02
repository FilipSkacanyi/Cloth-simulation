
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Application* app = nullptr;

	app = new Application();
	
	if (!app->Init())
	{
		return 0;
	}

	app->Run();


	delete app;
	app = nullptr;

	return 0;
}