// (window\cursors.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_WINDOW_CURSORS_H
#define BLAFCORE_WINDOW_CURSORS_H

namespace BLAF
{
	/** @brief Enumerator of default cursors. */
	enum class DefaultCursors
	{
		/** @brief Default arrow cursor. */
		Arrow				= 0,
		
		/** @brief I-Beam cursor (Text input cursor). */
		Ibeam				= 1,

		/** @brief Wait cursor (Hourglass / Rotating circle). */
		Wait				= 2,

		/** @brief Cross cursor (Graphical selection). */
		Cross				= 3,

		/** @brief Arrow pointing up cursor. */
		UpArrow				= 4,

		/** @brief Resize from northwest to southeast cursor. */
		ResizeNWSE			= 5,

		/** @brief Resize from northeast to southwest cursor. */
		ResizeNESW			= 6,

		/** @brief Resize horizontal cursor. */
		ResizeHorizontal	= 7,

		/** @brief Resize vertical cursor. */
		ResizeVertical		= 8,

		/** @brief Move cursor. */
		Move				= 9,

		/** @brief  */
		Denied				= 10,

		/** @brief  */
		Hand				= 11,

		/** @brief  */
		Loading				= 12,

		/** @brief  */
		Help				= 13,


		// Windows 10/11

		/** @brief Pin cursor (Location). */
		Pin					= 14,

		/** @brief Person cursor. */
		Person				= 15
	};
}

#endif