// (input\keycodes.h) This file is part of BLAF Input module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFINPUT_INPUT_KEYCODES_H
#define BLAFINPUT_INPUT_KEYCODES_H

namespace BLAF
{
	/** @brief List of all keyboard key codes. */
	enum class KeyCodes : uint8_t
	{
		Undefined			= 0x00,			// Undefined key
		
		// --Numeric keys--

		Numeric_0			= 0x01,			// 0 key
		Numeric_1			= 0x02,			// 1 key
		Numeric_2			= 0x03,			// 2 key
		Numeric_3			= 0x04,			// 3 key
		Numeric_4			= 0x05,			// 4 key
		Numeric_5			= 0x06,			// 5 key
		Numeric_6			= 0x07,			// 6 key
		Numeric_7			= 0x08,			// 7 key
		Numeric_8			= 0x09,			// 8 key
		Numeric_9			= 0x0A,			// 9 key
		
		// --Letter keys--

		Letter_A			= 0x0B,			// A key
		Letter_B			= 0x0C,			// B key
		Letter_C			= 0x0D,			// C key
		Letter_D			= 0x0E,			// D key
		Letter_E			= 0x0F,			// E key
		Letter_F			= 0x10,			// F key
		Letter_G			= 0x11,			// G key
		Letter_H			= 0x12,			// H key
		Letter_I			= 0x13,			// I key
		Letter_J			= 0x14,			// J key
		Letter_K			= 0x15,			// K key
		Letter_L			= 0x16,			// L key
		Letter_M			= 0x17,			// M key
		Letter_N			= 0x18,			// N key
		Letter_O			= 0x19,			// O key
		Letter_P			= 0x1A,			// P key
		Letter_Q			= 0x1B,			// Q key
		Letter_R			= 0x1C,			// R key
		Letter_S			= 0x1D,			// S key
		Letter_T			= 0x1E,			// T key
		Letter_U			= 0x1F,			// U key
		Letter_V			= 0x20,			// V key
		Letter_W			= 0x21,			// W key
		Letter_X			= 0x22,			// X key
		Letter_Y			= 0x23,			// Y key
		Letter_Z			= 0x24,			// Z key

		// --Modificators keys--

		Shift_Left			= 0x25,			// LEFT Shift
		Shift_Right			= 0x26,			// RIGHT Shift
		Shift				= 0x61,			// Shift

		Alt_Left			= 0x27,			// LEFT Alt
		Alt_Right			= 0x28,			// RIGHT Alt
		Alt					= 0x62,			// Alt
		
		Ctrl_Left			= 0x29,			// LEFT Ctrl
		Control_Left		= 0x29,			// LEFT Control (Alias to LEFT Ctrl)
		Ctrl_Right			= 0x2A,			// RIGHT Ctrl
		Control_Right		= 0x2A,			// RIGHT Control (Alias to RIGHT Ctrl)
		Ctrl				= 0x63,			// Ctrl
		Control				= 0x63,			// Control (Alias to Ctrl)

		// --Control keys--

		Spacebar			= 0x2B,			// Space / Space bar
		Backspace			= 0x2C,			// Backspace
		Escape				= 0x2D,			// Escape (ESC)
		Enter				= 0x2E,			// Enter
		Return				= 0x2E,			// Return (Alias to Enter)
		Application			= 0x2F,			// Application key (Key that opens context menu)
		Menu				= 0x2F,			// Menu (Alias to Application key)
		Tilde				= 0x30,			// Tilde
		Tab					= 0x31,			// Tab
		Meta_Left			= 0x32,			// LEFT Meta key
		Windows_Left		= 0x32,			// LEFT Windows key (Alias to LEFT Meta key)
		Meta_Right			= 0x33,			// RIGHT Meta key
		Windows_Right		= 0x33,			// RIGHT Windows key (Alias to RIGHT Meta key)
		Meta				= 0x64,			// Meta key
		Windows				= 0x64,			// Windows key (Alias to Meta key)

		// --"Lock" keys--

		CapsLock			= 0x34,			// Caps Lock
		NumLock				= 0x35,			// Num Lock
		ScrollLock			= 0x36,			// Scroll Lock

		// --Functional keys--

		F1					= 0x37,			// F1
		F2					= 0x38,			// F2
		F3					= 0x39,			// F3
		F4					= 0x3A,			// F4
		F5					= 0x3B,			// F5
		F6					= 0x3C,			// F6
		F7					= 0x3D,			// F7
		F8					= 0x3E,			// F8
		F9					= 0x3F,			// F9
		F10					= 0x40,			// F10
		F11					= 0x41,			// F11
		F12					= 0x42,			// F12
		
		// --"Math" keys--

		Minus				= 0x43,			// Minus key (-)
		Equal				= 0x44,			// Equal key (=)
		Semicolon			= 0x45,			// Semicolon key (;)
		Quote				= 0x46,			// Quote key (')
		Slash				= 0x47,			// Slash (/)
		Backslash			= 0x48,			// Back slash (\)

		// --Numpad keys--

		Numpad_0			= 0x49,			// 0 key on Numpad
		Numpad_1			= 0x4A,			// 1 key on Numpad
		Numpad_2			= 0x4B,			// 2 key on Numpad
		Numpad_3			= 0x4C,			// 3 key on Numpad
		Numpad_4			= 0x4D,			// 4 key on Numpad
		Numpad_5			= 0x4E,			// 5 key on Numpad
		Numpad_6			= 0x4F,			// 6 key on Numpad
		Numpad_7			= 0x50,			// 7 key on Numpad
		Numpad_8			= 0x51,			// 8 key on Numpad
		Numpad_9			= 0x52,			// 9 key on Numpad
		Numpad_Enter		= 0x53,			// Enter on Numpad
		Numpad_Return		= 0x53,			// Return on Numpad (Alias to Enter on Numpad)
		Numpad_Slash		= 0x54,			// Slash key (/) on Numpad
		Numpad_Asterisk		= 0x55,			// Asterisk key (*) on Numpad
		Numpad_Minus		= 0x56,			// Minus key (-) on Numpad
		Numpad_Plus			= 0x57,			// Plus key (+) on Numpad
		Numpad_Period		= 0x58,			// Period key (.) on Numpad
		
		// --Other keys--

		Period				= 0x59,			// Period key (.)
		Comma				= 0x5A,			// Comma key (,)
		Bracket_Left		= 0x5B,			// LEFT Bracket key ([ / {)
		Bracket_Right		= 0x5C,			// RIGHT Bracket key (] / })
		Delete				= 0x65,			// Delete key
		Insert				= 0x66,			// Insert key
		Home				= 0x67,			// Home key
		End					= 0x68,			// End key
		PageUp				= 0x69,			// Page Up key
		PageDown			= 0x6A,			// Page Down key

		// --Arrow keys--

		Arrow_Left			= 0x5D,			// LEFT Arrow key
		Arrow_Right			= 0x5E,			// RIGHT Arrow key
		Arrow_Up			= 0x5F,			// UP Arrow key
		Arrow_Down			= 0x60			// DOWN Arrow key
	};

	/** @brief List of all mouse codes. */
	enum class MouseCodes : uint8_t
	{
		Undefined			= 0x00,			// Undefined button

		LeftButton			= 0x01,			// LEFT Mouse button
		MiddleButton		= 0x02,			// MIDDLE Mouse button
		RightButton			= 0x03,			// RIGHT Mouse button
		
		ExtraButton1		= 0x04,			// 1st Extra Mouse button
		ExtraButton2		= 0x05,			// 2nd Extra Mouse button

		XButton1			= 0x04,			// Windows XButton 1 (Alias to 1st Extra Mouse button)
		XButton2			= 0x05			// Windows XButton 2 (Alias to 2nd Extra Mouse button)
	};

}

#endif