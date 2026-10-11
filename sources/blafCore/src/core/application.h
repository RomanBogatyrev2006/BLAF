#ifndef BLAFCORE_CORE_APPLICATION_H
#define BLAFCORE_CORE_APPLICATION_H

#include <logger/logger.h>

namespace BLAF
{
	/**
	* @brief Application class.
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