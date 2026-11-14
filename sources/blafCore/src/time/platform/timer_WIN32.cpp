// (time\platform\timer_WIN32.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS
#include <time/timer.h>
#include <chrono>
#include <logger/logger.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

namespace BLAF
{
	using clock = std::chrono::steady_clock;

	static clock::time_point sStartTime;
	static clock::time_point sLastFrame;

	clock::time_point* ToTimePoint(void* toConvert)
	{
		return static_cast<clock::time_point*>(toConvert);
	}

	void Timer::Initialize()
	{
		timeBeginPeriod(1);

		//delete static_cast<clock::time_point*>(sStartTime);
		//sStartTime = new clock::time_point(clock::now());
		//
		//delete static_cast<clock::time_point*>(sLastFrame);
		//sLastFrame = new clock::time_point(*ToTimePoint(sStartTime));

		sStartTime = clock::now();
		sLastFrame = sStartTime;

		sDeltaTime = 0.0;
		sFrameCounter = 0;
		sFPS = 0;
		sFPSTimer = 0.0;

		Log_INFO("(WIN32) Core timer initialized!");
	}

	void Timer::Tick()
	{
		clock::time_point now = clock::now();

		//sDeltaTime = std::chrono::duration<double>(now - *ToTimePoint(sLastFrame)).count();
		sDeltaTime = std::chrono::duration<double>(now - sLastFrame).count();
		sLastFrame = now;

		sFrameCounter++;
		sFPSTimer += sDeltaTime;

		if (sFPSTimer >= 1.0)
		{
			sFPS = sFrameCounter;
			sFrameCounter = 0;
			sFPSTimer -= 1.0;
		}
	}

	void Timer::Deinitialize()
	{
		timeEndPeriod(1);

		Log_INFO("(WIN32) Core timer deinitialized!");
		//delete static_cast<clock::time_point*>(sStartTime);
		//sStartTime = nullptr;
	}

	double Timer::GetTime()
	{
		//return std::chrono::duration<double>(clock::now() - *ToTimePoint(sStartTime)).count();
		return std::chrono::duration<double>(clock::now() - sStartTime).count();
	}

	double Timer::DeltaTime() { return sDeltaTime; }

	uint32_t Timer::GetFPS() { return sFPS; }

	double Timer::GetFrameTime()
	{
		return sFPS > 0 ? (1000.0 / static_cast<double>(sFPS)) : 0.0;
	}
}

#endif