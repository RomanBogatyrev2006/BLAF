// (core\application.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#include "application.h"

namespace BLAF
{
	Application::Application()
	{
		bRunning = false;

		// Initialize logger
		logger = new Logger();
	}

	Application::~Application()
	{
		logger->Log(LogLevel::Log, "Deinitializing...");

		// Deinitialize logger
		delete logger;
	}

	void Application::PostConstruct()
	{
	}

	void Application::Update()
	{
	}

	void Application::Run()
	{
		bRunning = true;
		logger->Log(LogLevel::Log, "Barely Lightweight Application Framework (BLAF)\n           -> VERSION: 0.0.0 DEBUG\n           -> BUILD DATE: 17.10.2026 (DD.MM.YYYY)\n           -> BUILD TIME: 1:21 (HH:MM)");
		PostConstruct();
		while (bRunning)
		{
			Update();
		}
	}

}

