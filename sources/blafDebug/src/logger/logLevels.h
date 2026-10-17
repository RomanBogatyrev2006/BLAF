// (logger\logLevels.h) This file is part of BLAF Debug module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFDEBUG_LOGGER_LOGLEVELS_H
#define BLAFDEBUG_LOGGER_LOGLEVELS_H

namespace BLAF
{
	/** @brief Specifies levels of Logging. */
	enum class LogLevel
	{
		/** @brief Log. */
		Log		= 0,
		
		/** @brief Information. */
		Info	= 1,

		/** @brief Warning. */
		Warning	= 2,

		/** @brief Error. */
		Error	= 3,

		/** @brief Fatal exception. */
		Fatal	= 4
	};
}

#endif