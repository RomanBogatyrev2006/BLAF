// (core\entrypoint.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_CORE_ENTRYPOINT_H
#define BLAFCORE_CORE_ENTRYPOINT_H

// ----EXAMPLE OF ENTRYPOINT USAGE----
// 
// 
// #include <core/application.h>
// #include <core/entrypoint.h>
// 
// BLAF_EntryPoint
// {
//     static Application* app = 0;
//     app = new Application(BLAF_GetLaunchArguments);
//     app->Run();
//     delete app;
//     return 0;
// }
// 
// 
// ----EXAMPLE OF ENTRYPOINT USAGE----

#include "launchArgs.h"

#ifdef BLAF_TARGET_WINDOWS
	#ifdef _DEBUG
		/** @brief An Entry point of BLAF. */
		#define BLAF_EntryPoint int main(int argc, char* argv[])
		/** @brief Get application's launch arguments. */
		#define BLAF_GetLaunchArguments BLAF::GetLaunchArguments(argc, argv)
	#else
		#include <Windows.h>
		/** @brief An Entry point of BLAF. */
		#define BLAF_EntryPoint int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
		/** @brief Get application's launch arguments. */
		#define BLAF_GetLaunchArguments BLAF::GetLaunchArguments(NULL, NULL)
	#endif
#else
	/** @brief An Entry point of BLAF. */
	#define BLAF_EntryPoint int main(int argc, char* argv[])
	/** @brief Get application's launch arguments. */
	#define BLAF_GetLaunchArguments BLAF::GetLaunchArguments(argc, argv)
#endif

#endif