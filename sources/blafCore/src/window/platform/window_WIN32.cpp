// (window\platform\window_WIN32.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS

#include <window/window.h>
#include <Windows.h>
#include <logger/logger.h>

namespace BLAF
{
	// Convert std::string to wstring (LPCWSTR)
	std::wstring UTF8toUTF16(const std::string& str)
	{
		if (str.empty()) return {};

		int size = MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS,
			str.c_str(),
			-1, nullptr, 0
		);

		if (size <= 0) return {};

		std::wstring result(size, L'\0');

		MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS,
			str.c_str(),
			-1, result.data(), size
		);

		result.pop_back();
		return result;
	};


	// --Monitors detection--

	struct MonitorDetect
	{
		HMONITOR target;
		int8_t index = -1;
		int8_t current = 0;
	};

	BOOL CALLBACK MonitorEnumProc(
		HMONITOR hMonitor,
		HDC,
		LPRECT,
		LPARAM data
	)
	{
		auto* detect = reinterpret_cast<MonitorDetect*>(data);

		if (hMonitor == detect->target)
		{
			detect->index = detect->current;
			return false;
		}

		++detect->current;
		return true;
	}

	uint8_t GetMonitorIndex(HWND hWnd)
	{
		HMONITOR target = MonitorFromWindow(
			hWnd, MONITOR_DEFAULTTONEAREST
		);

		if (!target) return -1;

		MonitorDetect detect{ target };

		EnumDisplayMonitors(
			nullptr,
			nullptr,
			MonitorEnumProc,
			reinterpret_cast<LPARAM>(&detect)
		);

		return detect.index;
	}


	// Win32API message operations
	LRESULT CALLBACK MessageHandling(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_CREATE:
			break;
		case WM_DESTROY:
			Log_INFO("(WIN32) Window destroyed!");
			//Application::logger->Log(LogLevel::Info, "Window destroyed!");
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_MOVE:
			//Application::logger->Log(LogLevel::Log, std::to_string(GetMonitorIndex(hWnd)));
			//Application::logger->Log(LogLevel::Fatal, std::to_string(LOWORD(lp)) + "x" + std::to_string(HIWORD(lp)));
			break;
		default: return DefWindowProc(hWnd, msg, wp, lp);
		}
		//return DefWindowProcA(hWnd, msg, wp, lp);
	}

	// Get WIN32 native window
	HWND GetNativeWindow(void* window)
	{
		return static_cast<HWND>(window);
	}


	// --Window--

	Window::Window(
		const std::string& title,
		uint32_t width,
		uint32_t height,
		uint32_t x,
		uint32_t y)
	{
		mProperties.title = title;
		mProperties.x = x;
		mProperties.y = y;
		mProperties.width = width;
		mProperties.height = height;

		mProperties.disableBorders = true;
		mProperties.disableMaximize = false;
		mProperties.disableMinimize = true;

		mCursor = DefaultCursors::Arrow;

		// Creating window class
		WNDCLASS winclass{};
		//winclass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
		//winclass.hCursor = LoadCursor(nullptr, IDC_CROSS);
		winclass.hInstance = GetModuleHandle(nullptr);
		winclass.lpfnWndProc = MessageHandling;
		winclass.lpszClassName = L"blafWndClass";

		if (!RegisterClass(&winclass))
		{
			Log_ERROR("(WIN32) Failed to register window class!");
			//Application::logger->Log(LogLevel::Error, "(WIN32) Failed to register window class!");
			return;
		}

		// Window flags
		long flags;
		flags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		if (mProperties.disableMaximize) { flags = flags | WS_MAXIMIZEBOX; }
		if (mProperties.disableMinimize) { flags = flags | WS_MINIMIZEBOX; }
		if (!mProperties.disableBorders) { flags = flags | WS_THICKFRAME; }

		// Converting window title
		std::wstring wideTitle = UTF8toUTF16(title);

		// Creating window
		HWND hWnd = CreateWindowW(
			winclass.lpszClassName,
			wideTitle.c_str(),
			flags,
			mProperties.x,
			mProperties.y,
			mProperties.width,
			mProperties.height,
			NULL,
			NULL,
			winclass.hInstance,
			NULL
		);

		// Check window handle
		if (!hWnd)
		{
			Log_ERROR("(WIN32) Failed to create window!");

			//Application::logger->Log(LogLevel::Error, "(WIN32) Failed to create window!");
			return;
		}

		// Set native window
		mNativeWindow = hWnd;

		uint8_t monitorID = GetMonitorIndex(hWnd);
		mProperties.monitor = monitorID;

		ShowWindow(hWnd, SW_SHOW);

		Log_INFO("(WIN32) Window was created successfully!");
		//Application::logger->Log(LogLevel::Info, "(WIN32) Window was created successfully!");
	}

	Window::~Window()
	{
		DestroyWindow(GetNativeWindow(mNativeWindow));
	}

	bool Window::Update()
	{
		MSG msg{};

		uint8_t monitorID = GetMonitorIndex(GetNativeWindow(mNativeWindow));
		mProperties.monitor = monitorID;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return false;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		return true;
	}

	void Window::SetPositionX(uint32_t x)
	{
		mProperties.x = x;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			x,
			GetPositionY(),
			0, 0,
			SWP_NOSIZE | SWP_NOZORDER
		);
	}

	void Window::SetPositionY(uint32_t y)
	{
		mProperties.y = y;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			GetPositionY(),
			y,
			0, 0,
			SWP_NOSIZE | SWP_NOZORDER
		);
	}

	void Window::SetPosition(uint32_t x, uint32_t y)
	{
		mProperties.x = x;
		mProperties.y = y;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			x,
			y,
			0, 0,
			SWP_NOSIZE | SWP_NOZORDER
		);
	}

	void Window::SetWidth(uint32_t width)
	{
		mProperties.width = width;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			0, 0,
			width,
			GetHeight(),
			SWP_NOMOVE | SWP_NOZORDER
		);
	}

	void Window::SetHeight(uint32_t height)
	{
		mProperties.height = height;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			0, 0,
			GetWidth(),
			height,
			SWP_NOMOVE | SWP_NOZORDER
		);
	}

	void Window::SetSize(uint32_t width, uint32_t height)
	{
		mProperties.width = width;
		mProperties.height = height;
		SetWindowPos(
			GetNativeWindow(mNativeWindow),
			nullptr,
			0, 0,
			width,
			height,
			SWP_NOMOVE | SWP_NOZORDER
		);
	}

	void Window::SetFullscreenMonitor(uint8_t monitor)
	{
		mProperties.monitorFullscreen = monitor;
	}

	void Window::SetFullscreenMode(FullscreenMode mode)
	{
		mProperties.fullscreenMode = mode;
	}

	void Window::SetVsync(bool enabled)
	{
		mProperties.vsync = enabled;
	}

	void ChangeCursor(DefaultCursors cursor)
	{
		switch (cursor)
		{
		case DefaultCursors::Arrow:
			SetCursor(LoadCursorW(NULL, IDC_ARROW));
			break;
		case DefaultCursors::Ibeam:
			SetCursor(LoadCursorW(NULL, IDC_IBEAM));
			break;
		case DefaultCursors::Wait:
			SetCursor(LoadCursorW(NULL, IDC_WAIT));
			break;
		case DefaultCursors::Cross:
			SetCursor(LoadCursorW(NULL, IDC_CROSS));
			break;
		case DefaultCursors::UpArrow:
			SetCursor(LoadCursorW(NULL, IDC_UPARROW));
			break;
		case DefaultCursors::ResizeNWSE:
			SetCursor(LoadCursorW(NULL, IDC_SIZENWSE));
			break;
		case DefaultCursors::ResizeNESW:
			SetCursor(LoadCursorW(NULL, IDC_SIZENESW));
			break;
		case DefaultCursors::ResizeHorizontal:
			SetCursor(LoadCursorW(NULL, IDC_SIZEWE));
			break;
		case DefaultCursors::ResizeVertical:
			SetCursor(LoadCursorW(NULL, IDC_SIZENS));
			break;
		case DefaultCursors::Move:
			SetCursor(LoadCursorW(NULL, IDC_SIZEALL));
			break;
		case DefaultCursors::Denied:
			SetCursor(LoadCursorW(NULL, IDC_NO));
			break;
		case DefaultCursors::Hand:
			SetCursor(LoadCursorW(NULL, IDC_HAND));
			break;
		case DefaultCursors::Loading:
			SetCursor(LoadCursorW(NULL, IDC_APPSTARTING));
			break;
		case DefaultCursors::Help:
			SetCursor(LoadCursorW(NULL, IDC_HELP));
			break;
		case DefaultCursors::Pin:
			SetCursor(LoadCursorW(NULL, IDC_PIN));
			break;
		case DefaultCursors::Person:
			SetCursor(LoadCursorW(NULL, IDC_PERSON));
			break;
		default:
			SetCursor(LoadCursorW(NULL, IDC_ARROW));
			break;
		}
	}

	void Window::SetCursor(DefaultCursors cursor)
	{
		ChangeCursor(cursor);
		mCursor = cursor;
	}

}

#endif