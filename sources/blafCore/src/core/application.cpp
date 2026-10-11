#include "application.h"

namespace BLAF
{
	Application::Application()
	{
		bRunning = false;
		logger = new Logger();
	}

	Application::~Application()
	{
		delete logger;
	}

	void Application::Run()
	{
		bRunning = true;
		while (bRunning)
		{
			
		}
	}
}

