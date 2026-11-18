// (window\window.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_WINDOW_WINDOW_H
#define BLAFCORE_WINDOW_WINDOW_H

#include "windowProps.h"
#include "cursors.h"
#include <input/input.h>

namespace BLAF
{
	/**	@brief Window class.
	*
	*	This class is responsible for creating application
	*	window and operate with it.
	*/
	class Window
	{
	public:
		/** @brief Constructor of class. */
		Window(
			const std::string& title = "BLAF",
			uint32_t width = 640,
			uint32_t height = 480,
			uint32_t x = -1,
			uint32_t y = -1,
			Input* input = nullptr
		);

		/** @brief Destructor of class. */
		~Window();


		/** @brief Update method. Calls on every application update. */
		bool Update();


		/**
		*	@name Setters
		*	@{
		*/

		/** @brief Set window position by X (Horizontal).
		* 
		*	@param x - New window position by X (Horizontal).
		*/
		void SetPositionX(uint32_t x);

		/** @brief Set window position by Y (Vertical).
		* 
		*	@param y - New window position by Y (Vertical).
		*/
		void SetPositionY(uint32_t y);

		/** @brief Set window position.
		* 
		*	@param x - New window position by X (Horizontal).
		* 
		*	@param y - New window position by Y (Vertical).
		*/
		void SetPosition(uint32_t x, uint32_t y);

		/** @brief Set window width (Horizontal size).
		* 
		*	@param width - New window width (Horizontal size).
		*/
		void SetWidth(uint32_t width);

		/** @brief Set window height (Vertical size).
		* 
		*	@param height - New window height (Vertical size).
		*/
		void SetHeight(uint32_t height);

		/** @brief Set window size.
		* 
		*	@param width - New window width (Horizontal size).
		* 
		*	@param height - New window height (Vertical size).
		*/
		void SetSize(uint32_t width, uint32_t height);

		/** @brief Set monitor ID on which window will be displayed in fullscreen mode.
		* 
		*	@param monitor - Numberic ID of monitor.
		*/
		void SetFullscreenMonitor(uint8_t monitor);

		/** @brief Set fullscreen mode of window.
		* 
		*	@param mode - Fullscreen mode.
		*/
		void SetFullscreenMode(FullscreenMode mode);

		/** @brief Set V-sync Enabled/Disabled.
		* 
		*	@param enabled - Enable V-sync or Disable?
		*/
		void SetVsync(bool enabled);

		/** @brief Set current default cursor.
		*
		*	@param cursor - Type of default cursor.
		*/
		void SetCursor(DefaultCursors cursor);

		/** @} */

		
		/**
		*	@name Getters
		*	@{
		*/

		/** @brief Get window position by X (Horizontal).
		*
		*	@return Position by X.
		*/
		const inline uint32_t GetPositionX() { return mProperties.x; }

		/** @brief Get window position by Y (Vertical).
		*
		*	@return Position by Y.
		*/
		const inline uint32_t GetPositionY() { return mProperties.y; }

		/** @brief Get window width (Horizontal size).
		*
		*	@return Width.
		*/
		const inline uint32_t GetWidth() { return mProperties.width; }

		/** @brief Get window height (Vertical size).
		*
		*	@return Height.
		*/
		const inline uint32_t GetHeight() { return mProperties.height; }

		/** @brief Get monitor ID on which a window is displayed.
		*
		*	@return Numeric ID of monitor.
		*/
		const inline uint8_t GetMonitor() { return mProperties.monitor; }

		/** @brief Get monitor ID on which a window will be displayed in fullscreen mode.
		*
		*	@return Numeric ID of monitor.
		*/
		const inline uint8_t GetFullscreenMonitor() { return mProperties.monitorFullscreen; }

		/** @brief Get fullscreen mode of window.
		*
		*	@return Fullscreen mode.
		*/
		const inline FullscreenMode GetFullscreenMode() { return mProperties.fullscreenMode; }

		/** @brief Is V-sync Enabled?
		*
		*	@return True, if V-sync enabled. Otherwise False.
		*/
		const inline bool GetVsync() { return mProperties.vsync; }

		/** @brief Get current default cursor.
		*
		*	@return Type of default cursor.
		*/
		const inline DefaultCursors GetCursor() { return mCursor; };

		//inline bool IsWindowOpened() { return true; }

		void* GetNativeWindow() { return mNativeWindow; }

		/** @} */

	private:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;


		/** @brief Window properties (Position, Size, Title, Fullscreen mode, etc). */
		WindowProperties mProperties;

		/** @brief Current cursor */
		DefaultCursors mCursor;

		/** @brief Native window handle. */
		void* mNativeWindow = nullptr;

		/** @brief Pointer to Input manager. */
		Input* mInputPointer = nullptr;
	};
}

#endif