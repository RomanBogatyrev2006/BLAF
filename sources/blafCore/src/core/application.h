// (core\application.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_CORE_APPLICATION_H
#define BLAFCORE_CORE_APPLICATION_H

#include <logger/logger.h>

namespace BLAF
{
	/**
	*	@brief Application class.
	* 
	*	This class is responsible for running the application.
	*	It contains application loops and modules responsible
	*	for the operation of application's various subsystems.
	*/
	class Application
	{
	public:
		/** @brief Constructor of class. */
		Application();
		
		/** @brief Destructor of class. */
		virtual ~Application();
		
		/** @brief Run application and its loops. */
		void Run();
		
		/** @brief Checks whether application is running.
		* 
		*	@return True, if application is running. Otherwise False.
		*/
		bool IsRunning() { return bRunning; }
		

		/** @brief Post construct method. Calls at end of class construction. */
		virtual void PostConstruct();

		/** @brief Update method. Calls on every application update (Overridable) */
		virtual void Update();


		/**
		*	@name Modules
		*	@{
		*/

		/** @brief Logger module. */
		inline static Logger* logger = 0;

		/** @} */

	private:
		/** @brief Indicates whether application is currently running. */
		bool bRunning;
	};

	
}

#endif