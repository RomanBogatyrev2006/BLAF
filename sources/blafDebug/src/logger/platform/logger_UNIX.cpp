// (logger\logger_UNIX.cpp) This file is part of BLAF Debug module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_UNIX
#include <logger/logger.h>
#include <fstream>
#include <sstream>

#include <time.h>

namespace BLAF
{
	Logger::Logger(const std::string& logFile)
		: mFile(new std::ofstream())
	{
		// Open log file
		static_cast<std::ofstream*>(mFile)->open(logFile, std::ofstream::app);
	}

	Logger::~Logger()
	{
		// Close log file
		if (static_cast<std::ofstream*>(mFile)->is_open())
		{
			static_cast<std::ofstream*>(mFile)->close();
		}

	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
#ifdef _DEBUG
		time_t raw_time;
		time(&raw_time);

		struct tm time_info;

		localtime_r(&raw_time, &time_info);

		std::ostringstream builder;

		// String = Set message color -> Time (HH:MM:SS) -> Message -> Reset message color
		builder << SetColor(level) <<
			std::setw(2) << std::setfill('0') << time_info.tm_hour << ":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_min << ":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_sec << "| " <<
			message << "\033[0m" << std::endl;

		WriteToConsole(level, builder.str());
		WriteToFile(level, builder.str());
#else
		if (static_cast<std::ofstream*>(mFile)->is_open())
		{
			time_t raw_time;
			time(&raw_time);

			struct tm time_info;

			localtime_r(&raw_time, &time_info);

			std::ostringstream builder;

			// String = Set message color -> Time (HH:MM:SS) -> Message -> Reset message color
			builder << SetColor(level) <<
				std::setw(2) << std::setfill('0') << time_info.tm_hour << ":" <<
				std::setw(2) << std::setfill('0') << time_info.tm_min << ":" <<
				std::setw(2) << std::setfill('0') << time_info.tm_sec << ":" <<
				message << "\033[0m" << std::endl;
			WriteToFile(level, message.str());
		}
#endif
	}

	void Logger::WriteToConsole(LogLevel level, const std::string& message)
	{
		std::cout << message;
	}

	void Logger::WriteToFile(LogLevel level, const std::string& message)
	{
		if (static_cast<std::ofstream*>(mFile)->is_open())
		{
			*static_cast<std::ofstream*>(mFile) << message << std::endl;
		}
	}

	const char* Logger::SetColor(LogLevel color)
	{
		switch (color)
		{
		case LogLevel::Log:		return "\033[37m";
		case LogLevel::Info:	return "\033[37m";
		case LogLevel::Warning:	return "\033[37m";
		case LogLevel::Error:	return "\033[37m";
		case LogLevel::Fatal:	return "\033[37m";
		default: return "\033[0m";
		}
	}
}
#endif
