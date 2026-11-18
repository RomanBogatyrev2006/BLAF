// (core\application.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_CORE_APPLICATION_H
#define BLAFCORE_CORE_APPLICATION_H

#include "launchArgs.h"
#include <logger/logger.h>
#include <window/window.h>
#include <render/render.h>
#include <time/timer.h>
#include <input/input.h>

namespace BLAF
{
	/**	@brief Application class.
	* 
	*	This class is responsible for running the application.
	*	It contains application loops and modules responsible
	*	for the operation of application's various subsystems.
	*/
	class Application
	{
	public:
		/** @brief Constructor of class. */
		Application(LaunchArguments launchArgs);
		
		/** @brief Destructor of class. */
		virtual ~Application();
		
		/** @brief Run application and its loops. */
		void Run();
		
		/** @brief Checks whether application is running.
		* 
		*	@return True, if application is running. Otherwise False.
		*/
		const bool IsRunning() { return bRunning; }
		

		/** @brief Post construct method. Calls at end of class construction (Overridable). */
		virtual void PostConstruct();

		/** @brief Update method. Calls on every application update (Overridable). */
		virtual void Update();

		/** @brief Render method. Calls on every application update (Overridable). */
		virtual void Render();


		/**
		*	@name Public modules
		*	@{
		*/

		/** @brief Logger module. */
		inline static Logger* logger = 0;

		/** @brief Renderer. */
		//inline static Renderer* renderer = 0;

		/** @} */

	protected:
		/**
		*	@name Protected modules
		*	@{
		*/

		/** @brief Timer. */
		inline static Timer* mTimer = 0;

		/** @brief Window. */
		inline static Window* mWindowManager = 0;

		/** @brief Input/ */
		inline static Input* mInput = 0;

		/** @} */

	private:
		/** @brief Indicates whether application is currently running. */
		bool bRunning;
		
	};

	
}

#endif