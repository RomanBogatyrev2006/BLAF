// (window\windowProps.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_WINDOW_WINDOWPROPS_H
#define BLAFCORE_WINDOW_WINDOWPROPS_H

/** @brief Specifies fullscreen modes for window. */
enum class FullscreenMode
{
	/** @brief Windowed mode. */
	Windowed			= 0,

	/** @brief Fullscreen mode. */
	Fullscreen			= 1,

	/** @brief Windowed but in fullscreen and without window's header. */
	WindowedFullscreen	= 2
};

/** @brief Structure of window properties. */
struct WindowProperties
{
	/** @name Window position
	*	@{
	*/

	/** @brief Position of window by X (Horizontal). */
	uint32_t x;

	/** @brief Position of window by Y (Vertical). */
	uint32_t y;

	/** @} */
	

	/** @name Window size
	*	@{
	*/

	/** @brief Width of window (Horizontal size). */
	uint32_t width;

	/** @brief Height of window (Vertical size). */
	uint32_t height;

	/** @} */


	/** @name Other window properties
	*	@{
	*/

	/** @brief On which monitor is window located. (If value is -1, window will be positioned on the primary monitor.) */
	uint8_t monitor;

	/** @brief On which monitor is fullscren window located. (If value is -1, window will be positioned on the primary monitor.) */
	uint8_t monitorFullscreen;

	/** @brief Fullscreen mode of window. */
	FullscreenMode fullscreenMode;

	/** @brief Is Vsync of window enabled. */
	bool vsync;

	/** @brief Window title. */
	std::string title;

	/** @brief Is Maximize button disabled. */
	bool disableMaximize;

	/** @brief Is Minimize button disabled. */
	bool disableMinimize;

	/** @brief Is Window borders innactive. */
	bool disableBorders;

	/** @} */
};

#endif