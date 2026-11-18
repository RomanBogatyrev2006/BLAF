// (core\application.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#include "application.h"
#include "core.h"

namespace BLAF
{
	Application::Application(LaunchArguments launchArgs)
	{
		bRunning = false;

		// Initialize logger
		#ifdef _DEBUG
			if (!launchArgs.logFile)
			{
				logger = new Logger();
			}
			else
			{
				logger = new Logger(launchArgs.logFile_Value);
			}
		#else
			if (!launchArgs.logFile)
			{
				logger = new Logger("");
			}
			else
			{
				logger = new Logger(launchArgs.logFile_Value);
			}
		#endif
		logger->Log(LogLevel::Log, BLAF_InitializeString);
		
		// Create input manager
		mInput = new Input();
		// Initialize window manager
		mWindowManager = new Window("BLAF", 1280, 720, 640, 360, mInput);
		//renderer = new Renderer();
		
	}

	Application::~Application()
	{
		logger->Log(LogLevel::Log, "Deinitializing...");
		
		// Deinitialize modules
		//delete renderer;
		delete mWindowManager;
		delete mInput;
		delete logger;
	}

	void Application::PostConstruct()
	{
	}

	void Application::Update()
	{
	}

	void Application::Render()
	{
	}

	void Application::Run()
	{
		bRunning = true;
		PostConstruct();
		mTimer->Initialize();
		mInput->Initialize(mWindowManager->GetNativeWindow());
		//renderer->Initialize();
		while (bRunning)
		{
			mTimer->Tick();
			bRunning = mWindowManager->Update();
			mInput->BeginFrame();
			mInput->Update(mTimer->DeltaTime());
			Update();
			mInput->EndFrame();

		}
		mTimer->Deinitialize();
		mInput->Deinitialize();
	}
}


