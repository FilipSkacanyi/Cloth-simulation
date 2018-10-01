#include "System.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	

	System* system = nullptr;
	bool result;


	// Create the system object.
	system = new System();
	if (!system)
	{
		MessageBox(NULL, "System not instantiated properly", "Error", NULL);
		return 0;
	}

	// Initialize and run the system object.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	// Shutdown and release the system object.
	system->Shutdown();
	delete system;
	system = nullptr;

	return 0;
}