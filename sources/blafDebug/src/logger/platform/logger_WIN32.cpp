// (logger\logger_WIN32.cpp) This file is part of BLAF Debug module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS
#include <logger/logger.h>
#include <fstream>
#include <sstream>
#include <core/application.h>

#include <time.h>
#include <Windows.h>

namespace BLAF
{
	Logger::Logger(const std::string& logFile)
		: mFile(new std::ofstream())
	{
		// Enable UTF8 encoding in Windows cmd
		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);

		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dwMode = 0;
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);

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

		localtime_s(&time_info, &raw_time);

		std::ostringstream builder;

		// String = Time (HH:MM:SS) -> Message
		builder << 
			std::setw(2) << std::setfill('0') << time_info.tm_hour << ":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_min << ":" <<
			std::setw(2) << std::setfill('0') << time_info.tm_sec << "| " <<
			message << std::endl;

		WriteToConsole(level, builder.str());
		WriteToFile(level, builder.str());
#else
		if (static_cast<std::ofstream*>(mFile)->is_open())
		{
			time_t raw_time;
			time(&raw_time);

			struct tm time_info;

			localtime_s(&time_info, &raw_time);

			std::ostringstream builder;

			// String = Time (HH:MM:SS) -> Message
			builder <<
				std::setw(2) << std::setfill('0') << time_info.tm_hour << ":" <<
				std::setw(2) << std::setfill('0') << time_info.tm_min << ":" <<
				std::setw(2) << std::setfill('0') << time_info.tm_sec << "| " <<
				message << std::endl;

			#ifdef _DEBUG
				WriteToFile(level, message.str());
			#else
				WriteToFile(level, message.c_str());
			#endif
			
		}
#endif
	}

	void Logger::WriteToConsole(LogLevel level, const std::string& message)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (hConsole == INVALID_HANDLE_VALUE)
		{
			std::cout << message;
			return;
		}
		
		// String = Set message color -> Log message -> Reset message color
		std::stringstream messageWithColor;
		messageWithColor << SetColor(level) << message << "\033[0m";
		std::string fullMessage = messageWithColor.str();

		std::string test = u8"Да ёпта иди сюды!dfh";

		int wide_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, fullMessage.data(), static_cast<int>(fullMessage.size()), nullptr, 0);
		
		if (wide_len <= 0)
		{
			DWORD error = GetLastError();

			std::cerr << "UTF-8 CONVERT FAIL. ERR: " << error << std::endl;
			std::cerr << "UTF-8 CONVERT FAIL. ERR: " << fullMessage.size() << std::endl;
			return;
		}
		
		std::wstring wide(wide_len, L'\0');
		MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, fullMessage.data(), static_cast<int>(fullMessage.size()), &wide[0], wide_len);
		DWORD written = 0;
		WriteConsoleW(hConsole, wide.c_str(), (DWORD)wcslen(wide.c_str()), &written, nullptr);
	}

	void Logger::WriteToFile(LogLevel level, const std::string& message)
	{
		if (static_cast<std::ofstream*>(mFile)->is_open())
		{
			*static_cast<std::ofstream*>(mFile) << message;
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


	// --Shortcuts--

	void Log_LOG(const std::string& message)
	{
		Application::logger->Log(LogLevel::Log, message);
	}
	
	void Log_INFO(const std::string& message)
	{
		Application::logger->Log(LogLevel::Info, message);
	}
	
	void Log_WARNING(const std::string& message)
	{
		Application::logger->Log(LogLevel::Warning, message);
	}
	
	void Log_ERROR(const std::string& message)
	{
		Application::logger->Log(LogLevel::Error, message);
	}
	
	void Log_FATAL(const std::string& message)
	{
		Application::logger->Log(LogLevel::Fatal, message);
	}

}
#endif
