// (input\input.h) This file is part of BLAF Input module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFINPUT_INPUT_INPUT_H
#define BLAFINPUT_INPUT_INPUT_H

#include "keycodes.h"

namespace BLAF
{
	/**	@brief Input (manager) class.
	*
	*	This class is responsible for managing framework's input.
	*	Supports raw input of keyboard and mouse!
	*/
	class Input
	{
	public:
		/** @brief Constructor of class. */
		Input();

		/** @brief Initialize method.
		*
		*	Initializes application's timer.
		* 
		*	@return True, if initialized successfully. Otherwise False.
		*/
		bool Initialize(void* nativeWindow);

		/** @brief Deinitialize method.
		*
		*	Deinitializes application's timer.
		*/
		void Deinitialize();

		/** @brief Begin frame method.
		*
		*	Calls on every begining of application update.
		*/
		void BeginFrame();

		/** @brief End frame method.
		*
		*	Calls on every ending of application update.
		*/
		void EndFrame();

		/** @brief Update method.
		*
		*	Calls on every application update.
		*/
		void Update(float DeltaTime);

		/** @brief Input handling method.
		*
		*	Handles raw input.
		*	This needs to be called on every input event/message of window.
		* 
		*	@param parameter - void pointer to special parameter from window.
		*/
		void InputHandling(void* parameter);
		
		/** @brief Mouse position handling method.
		*
		*	Handles mouse positions (Absolute and Relative).
		*	This needs to be called on every mouse movement event/message of window.
		*
		*	@param absoluteX - Absolute position of mouse by X.
		* 
		*	@param absoluteY - Absolute position of mouse by Y.
		* 
		*	@param relativeX - Relative position of mouse by X.
		* 
		*	@param relativeY - Relative position of mouse by Y.
		*/
		void MousePositionHandling(float absoluteX, float absoluteY, float relativeX, float relativeY);

		/** @brief Scan code to Key code converter method.
		*	
		*	Converts platform dependent scan code to platform independent framework's key code.
		* 
		*	@param scanCode - Scan code of key.
		* 
		*	@param parameter0 - First platform specific parameter.
		* 
		*	@param paremeter1 - Second platform specific parameter.
		* 
		*	@return Key code.
		*/
		static KeyCodes ConvertScanCodeToKeyCodes(uint16_t scanCode, bool parameter0, bool parameter1);

		/** @brief Key code to String of key converter method.
		*
		*	Converts framework's key code to the string representation of key code.
		*
		*	@param scanCode - Key code.
		* 
		*	@return String of key code.
		*/
		static std::string GetKeyCodeString(KeyCodes keyCode);

	private:
		/** @brief Mouse deltas by X and Y. */
		float mMouseDeltaX, mMouseDeltaY;

		/** @brief Absolute mouse positions by X and Y.
		*	
		*	Absolute - relative to screens.
		*/
		int32_t mMouseX, mMouseY;

		/** @brief Relative mouse positions by X and Y.
		*
		*	Relative - relative to framework's window.
		*/
		int32_t mMouseRelX, mMouseRelY;

		/** @brief Wheel scroll. */			// <---- NEED TO BE REDACTED!
		float mWheel;
	};
}

#endif