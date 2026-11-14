// (core\platform\launchArgs_UNIX.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_UNIX

#include <core/launchArgs.h>

namespace BLAF
{

	LaunchArguments GetLaunchArguments(int argc, char* argv[])
	{
		LaunchArguments result;

		for (int i = 1; i < argc; i++)
		{

			std::string argument = argv[i];

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
