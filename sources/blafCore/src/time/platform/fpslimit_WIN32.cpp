// (time\platform\fpslimit_WIN32.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS
#include <time/fpslimit.h>
#include <chrono>
#include <thread>

namespace BLAF
{
	using clock = std::chrono::steady_clock;

	static inline clock::time_point sNextFrameTime{};

	void FPSLimiter::BeginFrame()
	{
		if (sNextFrameTime.time_since_epoch().count() == 0)
			sNextFrameTime = clock::now();
	}

	void FPSLimiter::EndFrame()
	{
		if (!sEnabled || sTargetFPS <= 0) return;

		const clock::duration frameDuration = std::chrono::duration_cast<clock::duration>
			(std::chrono::duration<double>(1.0 / static_cast<double>(sTargetFPS)));

		clock::time_point now = clock::now();

		if (now > sNextFrameTime + frameDuration)
			sNextFrameTime = now;

		sNextFrameTime += frameDuration;

		if (now + std::chrono::microseconds(200) < sNextFrameTime)
		{
			std::this_thread::sleep_until(sNextFrameTime - std::chrono::microseconds(100));
		}

		while (clock::now() < sNextFrameTime) {}
	}

	void FPSLimiter::SetLimit(uint16_t fps) { sTargetFPS = fps > 0 ? fps : 0; }

	void FPSLimiter::SetEnabled(bool enabled) { sEnabled = enabled; }
}

#endif