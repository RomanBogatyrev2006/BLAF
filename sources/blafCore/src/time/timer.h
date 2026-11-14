// (time\timer.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_TIME_TIMER_H
#define BLAFCORE_TIME_TIMER_H

namespace BLAF
{
	/**	@brief Timer class.
	*	
	*	This class is responsible for handling application's timing,
	*	calculating and getting DeltaTime, FPS, etc.
	*/
	class Timer
	{
	public:
		/** @brief Initialize method. 
		*	
		*	Initializes application's timer.
		*/
		void Initialize();

		/** @brief Tick method.
		*	
		*	Calls on every application update.
		*/
		void Tick();

		/** @brief Deinitialize method.
		*
		*	Deinitializes application's timer.
		*/
		void Deinitialize();


		/** @brief Getter of current application's time. (static)
		*
		*	@return Current application's time.
		*/
		static double GetTime();

		/** @brief Getter of DeltaTime of application. (static)
		*
		*	@return Current DeltaTime.
		*/
		static double DeltaTime();


		/** @brief Getter of Frames per Second (FPS) of application. (static)
		*
		*	@return Current FPS.
		*/
		static uint32_t GetFPS();

		/** @brief Getter of current frame time of application. (static)
		*
		*	@return Current frame time.
		*/
		static double GetFrameTime();

	private:
		~Timer() { Deinitialize(); }

		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		//std::chrono::steady_clock::time_point
		//static void* sStartTime;

		//std::chrono::steady_clock::time_point
		//static void* sLastFrame;

		/** @brief Delta time value. */
		static inline double sDeltaTime = 0.0;


		/** @brief Frame counter. */
		static inline uint32_t sFrameCounter = 0;

		/** @brief Current FPS. */
		static inline uint32_t sFPS = 0;

		/** @brief FPS timer. */
		static inline double sFPSTimer = 0.0;
	};
}

#endif