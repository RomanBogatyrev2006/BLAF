// (input\platform\input_WIN32.h) This file is part of BLAF Input module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#include <input/input.h>
#include <logger/logger.h>
#include <Windows.h>

namespace BLAF
{
	// Register raw keyboard input
	bool RegisterKeyboard(HWND hwnd)
	{
		RAWINPUTDEVICE rid = {};
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x06;
		rid.dwFlags = RIDEV_INPUTSINK;
		rid.hwndTarget = hwnd;

		return RegisterRawInputDevices(&rid, 1, sizeof(rid));
	}

	// Register raw mouse input
	bool RegisterMouse(HWND hwnd)
	{
		RAWINPUTDEVICE rid = {};
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = RIDEV_INPUTSINK;
		rid.hwndTarget = hwnd;

		return RegisterRawInputDevices(&rid, 1, sizeof(rid));
	}

	Input::Input()
		:mMouseDeltaX(0.0f), mMouseDeltaY(0.0f),
		mMouseX(0), mMouseY(0), mMouseRelX(0), mMouseRelY(0),
		mWheel(0)
	{
	}

	bool Input::Initialize(void* nativeWindow)
	{
		if (!RegisterKeyboard(static_cast<HWND>(nativeWindow)))
		{
			Log_ERROR("(WIN32) Failed to register keyboard input!");
			return false;
		}
			

		if (!RegisterMouse(static_cast<HWND>(nativeWindow)))
		{
			Log_ERROR("(WIN32) Failed to register mouse input!");
			return false;
		}
		
		Log_ERROR("(WIN32) Input manager was initialized successfully!");
		return true;
	}

	void Input::Deinitialize()
	{

	}

	void Input::InputHandling(void* parameter)
	{
		// Convert platform dependent parameter to Win32API's LPARAM
		LPARAM windowParam = reinterpret_cast<LPARAM>(parameter);

		// --Keyboard--

		UINT kb_dwSize = 0;
		GetRawInputData((HRAWINPUT)windowParam, RID_INPUT, nullptr, &kb_dwSize, sizeof(RAWINPUTHEADER));
		
		if (kb_dwSize > 0)
		{
			std::vector<BYTE> lpb(kb_dwSize);
		
			if (GetRawInputData((HRAWINPUT)windowParam, RID_INPUT, lpb.data(), &kb_dwSize, sizeof(RAWINPUTHEADER)) == kb_dwSize)
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb.data());
				if (raw->header.dwType == RIM_TYPEKEYBOARD)
				{
					USHORT scanCode = raw->data.keyboard.MakeCode;
					USHORT flags = raw->data.keyboard.Flags;
					USHORT vKey = raw->data.keyboard.VKey;
		
					bool isKeyUp = (flags & RI_KEY_BREAK) != 0;
					bool isKeyDown = (flags & RI_KEY_BREAK) == 0;
					bool isE0 = (flags & RI_KEY_E0) != 0;
					bool isE1 = (flags & RI_KEY_E1) != 0;
		
					KeyCodes kc = ConvertScanCodeToKeyCodes(scanCode, isE0, isE1);
					if (kc != KeyCodes::Undefined)
					{
						if (isKeyUp)
						{
							//Log_LOG("RELEASED: " + GetKeyCodeString(kc));
						}
						if (isKeyDown)
						{
							Log_LOG("PRESSED:  " + GetKeyCodeString(kc));
						}
					}
				}
			}
		}

		// --Mouse--

		UINT ms_dwSize = 0;
		GetRawInputData((HRAWINPUT)windowParam, RID_INPUT, nullptr, &ms_dwSize, sizeof(RAWINPUTHEADER));

		if (ms_dwSize > 0)
		{
			std::vector<BYTE> ms_lpb(ms_dwSize);

			if (GetRawInputData((HRAWINPUT)windowParam, RID_INPUT, ms_lpb.data(), &ms_dwSize, sizeof(RAWINPUTHEADER)) == ms_dwSize)
			{
				RAWINPUT* msRaw = reinterpret_cast<RAWINPUT*>(ms_lpb.data());
				if (msRaw->header.dwType == RIM_TYPEMOUSE)
				{
					USHORT buttonFlags = msRaw->data.mouse.usButtonFlags;
					USHORT flags = msRaw->data.mouse.usFlags;
					USHORT buttonData = msRaw->data.mouse.usButtonData;
					LONG lastX = msRaw->data.mouse.lLastX;
					LONG lastY = msRaw->data.mouse.lLastY;
					
					bool isMouse1Up = (buttonFlags & RI_MOUSE_LEFT_BUTTON_UP);
					bool isMouse1Down = (buttonFlags & RI_MOUSE_LEFT_BUTTON_DOWN);

					bool isMouse2Up = (buttonFlags & RI_MOUSE_RIGHT_BUTTON_UP);
					bool isMouse2Down = (buttonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN);

					bool isMouse3Up = (buttonFlags & RI_MOUSE_MIDDLE_BUTTON_UP);
					bool isMouse3Down = (buttonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN);

					bool isMouse4Up = (buttonFlags & RI_MOUSE_BUTTON_4_UP);
					bool isMouse4Down = (buttonFlags & RI_MOUSE_BUTTON_4_DOWN);

					bool isMouse5Up = (buttonFlags & RI_MOUSE_BUTTON_5_UP);
					bool isMouse5Down = (buttonFlags & RI_MOUSE_BUTTON_5_DOWN);

					if (buttonFlags & RI_MOUSE_WHEEL)
					{
						SHORT wheelDelta = (SHORT)buttonData;
						mWheel = -wheelDelta / 10.0f;
						std::cout << mWheel << std::endl;
					}

					mMouseDeltaX = lastX/10.0f;
					mMouseDeltaY = lastY/10.0f;

				}
			}
		}
	}

	void  Input::MousePositionHandling(float absoluteX, float absoluteY, float relativeX, float relativeY)
	{
		mMouseX = absoluteX;
		mMouseY = absoluteY;

		mMouseRelX = relativeX;
		mMouseRelY = relativeY;
	}

	void Input::BeginFrame()
	{
		
	}

	void Input::EndFrame()
	{
		mMouseDeltaX = 0;
		mMouseDeltaY = 0;
	}

	void Input::Update(float DeltaTime)
	{
		
	}


	KeyCodes Input::ConvertScanCodeToKeyCodes(uint16_t scanCode, bool parameter0, bool parameter1)
	{
		bool fakeShift = (scanCode == 0x2A) && (parameter0);

		//if (fakeShift) { Log_ERROR("FAKE SHIFT DETECTED!"); }
		//else { Log_ERROR("Normal key"); }

		//if (!parameter0) { return KeyCodes::Shift_Left; break; }
		//		else break;

		switch (scanCode)
		{
		case 0x01:
			return KeyCodes::Escape; break;
		case 0x02:
			return KeyCodes::Numeric_1; break;
		case 0x03:
			return KeyCodes::Numeric_2; break;
		case 0x04:
			return KeyCodes::Numeric_3; break;
		case 0x05:
			return KeyCodes::Numeric_4; break;
		case 0x06:
			return KeyCodes::Numeric_5; break;
		case 0x07:
			return KeyCodes::Numeric_6; break;
		case 0x08:
			return KeyCodes::Numeric_7; break;
		case 0x09:
			return KeyCodes::Numeric_8; break;
		case 0x0A:
			return KeyCodes::Numeric_9; break;
		case 0x0B:
			return KeyCodes::Numeric_0; break;
		case 0x0C:
			return KeyCodes::Minus; break;
		case 0x0D:
			return KeyCodes::Equal; break;
		case 0x0E:
			return KeyCodes::Backspace; break;
		case 0x0F:
			return KeyCodes::Tab; break;
		case 0x10:
			return KeyCodes::Letter_Q; break;
		case 0x11:
			return KeyCodes::Letter_W; break;
		case 0x12:
			return KeyCodes::Letter_E; break;
		case 0x13:
			return KeyCodes::Letter_R; break;
		case 0x14:
			return KeyCodes::Letter_T; break;
		case 0x15:
			return KeyCodes::Letter_Y; break;
		case 0x16:
			return KeyCodes::Letter_U; break;
		case 0x17:
			return KeyCodes::Letter_I; break;
		case 0x18:
			return KeyCodes::Letter_O; break;
		case 0x19:
			return KeyCodes::Letter_P; break;
		case 0x1A:
			return KeyCodes::Bracket_Left; break;
		case 0x1B:
			return KeyCodes::Bracket_Right; break;
		case 0x1C:
		{
			if (parameter0) { return KeyCodes::Numpad_Enter; break; }
			else { return KeyCodes::Enter; break; }
		}
		case 0x1D:
		{
			if (parameter0) { return KeyCodes::Ctrl_Right; break; }
			else { return KeyCodes::Ctrl_Left; break; }
		}
		case 0x1E:
			return KeyCodes::Letter_A; break;
		case 0x1F:
			return KeyCodes::Letter_S; break;
		case 0x20:
			return KeyCodes::Letter_D; break;
		case 0x21:
			return KeyCodes::Letter_F; break;
		case 0x22:
			return KeyCodes::Letter_G; break;
		case 0x23:
			return KeyCodes::Letter_H; break;
		case 0x24:
			return KeyCodes::Letter_J; break;
		case 0x25:
			return KeyCodes::Letter_K; break;
		case 0x26:
			return KeyCodes::Letter_L; break;
		case 0x27:
			return KeyCodes::Semicolon; break;
		case 0x28:
			return KeyCodes::Quote; break;
		case 0x29:
			return KeyCodes::Tilde; break;
		case 0x2A:
			//return KeyCodes::Shift_Left; break;
			if (!parameter0) { return KeyCodes::Shift_Left; break; }
			else return KeyCodes::Undefined;
		case 0x2B:
			return KeyCodes::Backslash; break;
		case 0x2C:
			return KeyCodes::Letter_Z; break;
		case 0x2D:
			return KeyCodes::Letter_X; break;
		case 0x2E:
			return KeyCodes::Letter_C; break;
		case 0x2F:
			return KeyCodes::Letter_V; break;
		case 0x30:
			return KeyCodes::Letter_B; break;
		case 0x31:
			return KeyCodes::Letter_N; break;
		case 0x32:
			return KeyCodes::Letter_M; break;
		case 0x33:
			return KeyCodes::Comma; break;
		case 0x34:
			return KeyCodes::Period; break;
		case 0x35:
		{
			if (parameter0) { return KeyCodes::Numpad_Slash; break; }
			else { return KeyCodes::Slash; break; }
		}
		case 0x36:
			return KeyCodes::Shift_Right; break;
		case 0x37:
			return KeyCodes::Numpad_Asterisk; break;
		case 0x38:
		{
			if (parameter0) { return KeyCodes::Alt_Right; break; }
			else { return KeyCodes::Alt_Left; break; }
		}
		case 0x39:
			return KeyCodes::Spacebar; break;
		case 0x3A:
			return KeyCodes::CapsLock; break;
		case 0x3B:
			return KeyCodes::F1; break;
		case 0x3C:
			return KeyCodes::F2; break;
		case 0x3D:
			return KeyCodes::F3; break;
		case 0x3E:
			return KeyCodes::F4; break;
		case 0x3F:
			return KeyCodes::F5; break;
		case 0x40:
			return KeyCodes::F6; break;
		case 0x41:
			return KeyCodes::F7; break;
		case 0x42:
			return KeyCodes::F8; break;
		case 0x43:
			return KeyCodes::F9; break;
		case 0x44:
			return KeyCodes::F10; break;
		case 0x45:
			return KeyCodes::NumLock; break;
		case 0x46:
			return KeyCodes::ScrollLock; break;
		case 0x47:
		{
			if (parameter0) { return KeyCodes::Home; break; }
			else { return KeyCodes::Numpad_7; break; }
		}
		case 0x48:
		{
			if (parameter0) { return KeyCodes::Arrow_Up; break; }
			else { return KeyCodes::Numpad_8; break; }
		}
		case 0x49:
		{
			if (parameter0) { return KeyCodes::PageUp; break; }
			else { return KeyCodes::Numpad_9; break; }
		}
		case 0x4A:
			return KeyCodes::Numpad_Minus; break;
		case 0x4B:
		{
			if (parameter0) { return KeyCodes::Arrow_Left; break; }
			else { return KeyCodes::Numpad_4; break; }
		}
		case 0x4C:
			return KeyCodes::Numpad_5; break;
		case 0x4D:
		{
			if (parameter0) { return KeyCodes::Arrow_Right; break; }
			else { return KeyCodes::Numpad_6; break; }
		}
		case 0x4E:
			return KeyCodes::Numpad_Plus; break;
		case 0x4F:
		{
			if (parameter0) { return KeyCodes::End; break; }
			else { return KeyCodes::Numpad_1; break; }
		}
		case 0x50:
		{
			if (parameter0) { return KeyCodes::Arrow_Down; break; }
			else { return KeyCodes::Numpad_2; break; }
		}
		case 0x51:
		{
			if (parameter0) { return KeyCodes::PageDown; break; }
			else { return KeyCodes::Numpad_3; break; }
		}
		case 0x52:
		{
			if (parameter0) { return KeyCodes::Insert; break; }
			else { return KeyCodes::Numpad_0; break; }
		}
		case 0x53:
		{
			if (parameter0) { return KeyCodes::Delete; break; }
			else { return KeyCodes::Numpad_Period; break; }
		}
		case 0x54:
			return KeyCodes::Undefined; break; // Alt-SysRq
		case 0x55:
			return KeyCodes::Undefined; break;
		case 0x56:
			return KeyCodes::Undefined; break;
		case 0x57:
			return KeyCodes::F11; break;
		case 0x58:
			return KeyCodes::F12; break;
		case 0x59:
			return KeyCodes::Undefined; break;
		case 0x5A:
			return KeyCodes::Undefined; break;
		case 0x5B:
			return KeyCodes::Meta_Left; break;
		case 0x5C:
			return KeyCodes::Meta_Right; break;
		case 0x5D:
			return KeyCodes::Application; break;
		default:
			return KeyCodes::Undefined; break;
		};
		return KeyCodes::Undefined;
	}

	std::string Input::GetKeyCodeString(KeyCodes keyCode)
	{
		switch (keyCode)
		{
			case KeyCodes::Numeric_0:
				return "0"; break;
			case KeyCodes::Numeric_1:
				return "1"; break;
			case KeyCodes::Numeric_2:
				return "2"; break;
			case KeyCodes::Numeric_3:
				return "3"; break;
			case KeyCodes::Numeric_4:
				return "4"; break;
			case KeyCodes::Numeric_5:
				return "5"; break;
			case KeyCodes::Numeric_6:
				return "6"; break;
			case KeyCodes::Numeric_7:
				return "7"; break;
			case KeyCodes::Numeric_8:
				return "8"; break;
			case KeyCodes::Numeric_9:
				return "9"; break;

			case KeyCodes::Letter_A:
				return "A"; break;
			case KeyCodes::Letter_B:
				return "B"; break;
			case KeyCodes::Letter_C:
				return "C"; break;
			case KeyCodes::Letter_D:
				return "D"; break;
			case KeyCodes::Letter_E:
				return "E"; break;
			case KeyCodes::Letter_F:
				return "F"; break;
			case KeyCodes::Letter_G:
				return "G"; break;
			case KeyCodes::Letter_H:
				return "H"; break;
			case KeyCodes::Letter_I:
				return "I"; break;
			case KeyCodes::Letter_J:
				return "J"; break;
			case KeyCodes::Letter_K:
				return "K"; break;
			case KeyCodes::Letter_L:
				return "L"; break;
			case KeyCodes::Letter_M:
				return "M"; break;
			case KeyCodes::Letter_N:
				return "N"; break;
			case KeyCodes::Letter_O:
				return "O"; break;
			case KeyCodes::Letter_P:
				return "P"; break;
			case KeyCodes::Letter_Q:
				return "Q"; break;
			case KeyCodes::Letter_R:
				return "R"; break;
			case KeyCodes::Letter_S:
				return "S"; break;
			case KeyCodes::Letter_T:
				return "T"; break;
			case KeyCodes::Letter_U:
				return "U"; break;
			case KeyCodes::Letter_V:
				return "V"; break;
			case KeyCodes::Letter_W:
				return "W"; break;
			case KeyCodes::Letter_X:
				return "X"; break;
			case KeyCodes::Letter_Y:
				return "Y"; break;
			case KeyCodes::Letter_Z:
				return "Z"; break;

			case KeyCodes::Shift_Left:
				return "Left Shift"; break;
			case KeyCodes::Shift_Right:
				return "Right Shift"; break;
			case KeyCodes::Shift:
				return "Shift"; break;
			case KeyCodes::Alt_Left:
				return "Left Alt"; break;
			case KeyCodes::Alt_Right:
				return "Right Alt"; break;
			case KeyCodes::Alt:
				return "Alt"; break;
			case KeyCodes::Ctrl_Left:
				return "Left Ctrl"; break;
			case KeyCodes::Ctrl_Right:
				return "Right Ctrl"; break;
			case KeyCodes::Ctrl:
				return "Ctrl"; break;

			case KeyCodes::Spacebar:
				return "Space bar"; break;
			case KeyCodes::Backspace:
				return "Backspace"; break;
			case KeyCodes::Escape:
				return "Escape"; break;
			case KeyCodes::Enter:
				return "Enter"; break;
			case KeyCodes::Application:
				return "Application"; break;
			case KeyCodes::Tilde:
				return "Tilde"; break;
			case KeyCodes::Tab:
				return "Tab"; break;
			case KeyCodes::Meta_Left:
				return "Left Windows"; break;
			case KeyCodes::Meta_Right:
				return "Right Windows"; break;
			case KeyCodes::Meta:
				return "Windows"; break;

			case KeyCodes::CapsLock:
				return "Caps Lock"; break;
			case KeyCodes::NumLock:
				return "Num Lock"; break;
			case KeyCodes::ScrollLock:
				return "Scroll Lock"; break;

			case KeyCodes::F1:
				return "F1"; break;
			case KeyCodes::F2:
				return "F2"; break;
			case KeyCodes::F3:
				return "F3"; break;
			case KeyCodes::F4:
				return "F4"; break;
			case KeyCodes::F5:
				return "F5"; break;
			case KeyCodes::F6:
				return "F6"; break;
			case KeyCodes::F7:
				return "F7"; break;
			case KeyCodes::F8:
				return "F8"; break;
			case KeyCodes::F9:
				return "F9"; break;
			case KeyCodes::F10:
				return "F10"; break;
			case KeyCodes::F11:
				return "F11"; break;
			case KeyCodes::F12:
				return "F12"; break;

			case KeyCodes::Minus:
				return "Minus"; break;
			case KeyCodes::Equal:
				return "Equal"; break;
			case KeyCodes::Semicolon:
				return "Semicolon"; break;
			case KeyCodes::Quote:
				return "Quote"; break;
			case KeyCodes::Slash:
				return "Slash"; break;
			case KeyCodes::Backslash:
				return "Backslash"; break;

			case KeyCodes::Numpad_0:
				return "Numpad 0"; break;
			case KeyCodes::Numpad_1:
				return "Numpad 1"; break;
			case KeyCodes::Numpad_2:
				return "Numpad 2"; break;
			case KeyCodes::Numpad_3:
				return "Numpad 3"; break;
			case KeyCodes::Numpad_4:
				return "Numpad 4"; break;
			case KeyCodes::Numpad_5:
				return "Numpad 5"; break;
			case KeyCodes::Numpad_6:
				return "Numpad 6"; break;
			case KeyCodes::Numpad_7:
				return "Numpad 7"; break;
			case KeyCodes::Numpad_8:
				return "Numpad 8"; break;
			case KeyCodes::Numpad_9:
				return "Numpad 9"; break;
			case KeyCodes::Numpad_Enter:
				return "Numpad Enter"; break;
			case KeyCodes::Numpad_Slash:
				return "Numpad Slash"; break;
			case KeyCodes::Numpad_Asterisk:
				return "Numpad Asterisk"; break;
			case KeyCodes::Numpad_Minus:
				return "Numpad Minus"; break;
			case KeyCodes::Numpad_Plus:
				return "Numpad Plus"; break;
			case KeyCodes::Numpad_Period:
				return "Numpad Period"; break;

			case KeyCodes::Period:
				return "Period"; break;
			case KeyCodes::Comma:
				return "Comma"; break;
			case KeyCodes::Bracket_Left:
				return "Left Bracket"; break;
			case KeyCodes::Bracket_Right:
				return "Right Bracket"; break;
			case KeyCodes::Delete:
				return "Delete"; break;
			case KeyCodes::Insert:
				return "Insert"; break;
			case KeyCodes::Home:
				return "Home"; break;
			case KeyCodes::End:
				return "End"; break;
			case KeyCodes::PageUp:
				return "Page Up"; break;
			case KeyCodes::PageDown:
				return "Page Down"; break;

			case KeyCodes::Arrow_Left:
				return "Arrow Left"; break;
			case KeyCodes::Arrow_Right:
				return "Arrow Right"; break;
			case KeyCodes::Arrow_Up:
				return "Arrow Up"; break;
			case KeyCodes::Arrow_Down:
				return "Arrow Down"; break;
			default:
				return "Undefined"; break;
		}
		return "Undefined";
	}
	
}