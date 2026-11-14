// (time\fpslimit.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_TIME_FPSLIMIT_H
#define BLAFCORE_TIME_FPSLIMIT_H

namespace BLAF
{
	/// NEED COMMENTS!!!
	class FPSLimiter
	{
	public:
		
		void BeginFrame();

		void EndFrame();

		static void SetLimit(uint16_t fps);

		static void SetEnabled(bool enabled);

	private:
		static inline bool sEnabled = false;
		static inline uint16_t sTargetFPS = 60;
	};
}

#endif
