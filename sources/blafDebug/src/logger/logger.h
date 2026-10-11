#ifndef BLAFDEBUG_LOGGER_LOGGER_H
#define BLAFDEBUG_LOGGER_LOGGER_H

#include "logLevels.h"

namespace BLAF
{
	/**
	* @brief Logger class.
	*
	*	This class is responsible for logging.
	*	Supports logging to the console and to a separate log file.
	*	In Debug configuration, logging to both the console and the file is enabled.
	*	In Release configuration, logging is enabled only to the file (which must be
	*	specified when launching the application).
	*/
	class Logger
	{
	public:
#ifdef _DEBUG
		/** @brief Constructor of class. 
		*	
		*	Initializes logger and log file (if log file was specified).
		*	
		*	@param logFile - path and name of log file.
		*/
		Logger(const std::string& logFile = "log.txt");
#else
		/** @brief Constructor of class.
		*
		*	Initializes logger and log file (if log file was specified).
		*
		*	@param logFile - path and name of log file.
		*/
		Logger(const std::string& logFile);
#endif

		/** @brief Destructor of class. */
		~Logger();

		/** @brief Log message.
		* 
		*	This method logs to the console and to log file (if log file was specified).
		*	
		*	@param level - Level of logging.
		*	@param message - Message to log.
		*/
		void Log(LogLevel level, const std::string& message);

	private:
		Logger(const Logger&) = delete;

		Logger& operator=(const Logger&) = delete;

		/** @brief Print message to console.
		* 
		*	@param level - Level of logging.
		*	@param message - Message to log.
		*/
		void WriteToConsole(LogLevel level, const std::string& message);

		/** @brief Print message to log file.
		* 
		*	@param level - Level of logging.
		*	@param message - Message to log.
		*/
		void WriteToFile(LogLevel level, const std::string& message);

		/** @brief Set console text color.
		* 
		*	Using this in log message chain.
		*	
		*	@param color - Color of log message based on log level.
		*	
		*	@return ANSI color code.
		*/
		const char* SetColor(LogLevel color);

		// |LEVEL    |COLOR          |ANSI      |
		// |---------|---------------|----------|
		// | Log	 | White		 |"\033[37m"|
		// | Info	 | Light blue	 |"\033[94m"|
		// | Warning | Yellow		 |"\033[33m"|
		// | Error	 | Red			 |"\033[31m"|
		// | Fatal	 | Bright red	 |"\033[91m"|


		/** @brief Log file. */
		void* mFile = nullptr;

	};
}

#endif