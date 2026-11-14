// (core\platform\launchArgs_WIN32.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS

#include <core/launchArgs.h>
#include <Windows.h>

namespace BLAF
{

	LaunchArguments GetLaunchArguments(int argc, char* argv[])
	{
		LaunchArguments result;


		// Getting command line arguments
		// https://codingmisadventures.wordpress.com/2009/03/10/retrieving-command-line-parameters-from-winmain-in-win32/
		// This is from 2009 and it DOES in big and cursed 2026!

		LPWSTR* szArgList;
		int argCount;

		szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
		if (szArgList == NULL)
		{
			return {false, "", false};
		}

		// Converting command line arguments into ArgC and ArgV.

		std::vector<std::string> cmdArguments;

		for (int i = 0; i < argCount; i++)
		{
			int size = WideCharToMultiByte(
				CP_UTF8, 0,
				szArgList[i], -1,
				nullptr, 0,
				nullptr, nullptr
			);

			std::string cmdArgument(size - 1, '\0');

			WideCharToMultiByte(
				CP_UTF8, 0,
				szArgList[i], -1,
				cmdArgument.data(), size,
				nullptr, nullptr
			);

			cmdArguments.push_back(cmdArgument);
		}

		LocalFree(szArgList);

		std::vector<char*> cmdArgv;

		for (std::string& arg : cmdArguments)
			cmdArgv.push_back(arg.data());

		int cmdArgc = static_cast<int>(cmdArgv.size());



		for (int i = 1; i < cmdArgc; i++)
		{

			std::string argument = cmdArgv.data()[i];

			// Checking for -
			if (argument.empty() || argument[0] != '-') continue;

			// Checking for =
			size_t equalPos = argument.find('=');

			// Flag parameters
			if (equalPos == std::string::npos)
			{
				if (argument == "-noaudio")
				{
					result.noAudio = true;
				}
				continue;
			}

			std::string name = argument.substr(0, equalPos);

			std::string value = argument.substr(equalPos + 1);

			// Parameters with value
			if (name == "-logfile")
			{
				result.logFile = true;
				result.logFile_Value = value;
			}
		}
		return result;
	};

}

#endif
