// (window\platform\window_WIN32.cpp) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifdef BLAF_TARGET_WINDOWS

#include <window/window.h>
#include <Windows.h>
#include <core/application.h>

namespace BLAF
{
	// --Monitors detection--

	struct MonitorDetect
	{
		HMONITOR target;
		uint8_t index = -1;
		uint8_t current = 0;
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
			Application::logger->Log(LogLevel::Info, "Window destroyed!");
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

		// Creating window class
		WNDCLASS winclass{};
		//winclass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
		winclass.hCursor = LoadCursor(nullptr, IDC_CROSS);
		winclass.hInstance = GetModuleHandle(nullptr);
		winclass.lpfnWndProc = MessageHandling;
		winclass.lpszClassName = "blafWndClass";

		if (!RegisterClass(&winclass))
		{
			Application::logger->Log(LogLevel::Error, "Failed to register window class!");
			return;
		}

		// Window flags
		long flags;
		flags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		if (mProperties.disableMaximize) { flags = flags | WS_MAXIMIZEBOX; }
		if (mProperties.disableMinimize) { flags = flags | WS_MINIMIZEBOX; }
		if (!mProperties.disableBorders) { flags = flags | WS_THICKFRAME; }

		// Creating window
		HWND hWnd = CreateWindow(
			winclass.lpszClassName,
			title.c_str(),
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
			Application::logger->Log(LogLevel::Error, "Failed to create window!");
			return;
		}

		// Set native window
		mNativeWindow = hWnd;

		uint8_t monitorID = GetMonitorIndex(hWnd);
		mProperties.monitor = monitorID;

		ShowWindow(hWnd, SW_SHOW);
	}

	Window::~Window()
	{

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
}

#endif