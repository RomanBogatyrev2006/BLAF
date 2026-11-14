// (core\launchArgs.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_CORE_LAUNCHARGS_H
#define BLAFCORE_CORE_LAUNCHARGS_H

namespace BLAF
{
	/** @brief Structure of launch arguments.
	*	
	*	List of application's launch arguments.
	*/
	struct LaunchArguments
	{
		/** @brief Log file was provided. */
		bool logFile = false;

		/** @brief Log file path/name. */
		std::string logFile_Value = "";


		/** @brief Audio will be disable. */
		bool noAudio = false;
	};
	
	/** @brief Get launch arguments from given data. */
	LaunchArguments GetLaunchArguments(int argc, char* argv[]);
	
}

#endif