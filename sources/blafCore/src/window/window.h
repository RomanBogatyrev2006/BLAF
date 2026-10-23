// (window\window.h) This file is part of BLAF Core module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFCORE_WINDOW_WINDOW_H
#define BLAFCORE_WINDOW_WINDOW_H

#include "windowProps.h"

namespace BLAF
{
	class Window
	{
	public:
		Window(
			const std::string& title = "BLAF",
			uint32_t width = 640,
			uint32_t height = 480,
			uint32_t x = -1,
			uint32_t y = -1
		);

		~Window();


		bool Update();


		////// SETTERS!!!!!!!!

		void SetPositionX(uint32_t x);

		void SetPositionY(uint32_t y);

		void SetPosition(uint32_t x, uint32_t y);

		void SetWidth(uint32_t width);

		void SetHeight(uint32_t height);

		void SetSize(uint32_t width, uint32_t height);

		void SetFullscreenMonitor(uint8_t monitor);

		void SetFullscreenMode(FullscreenMode mode);

		void SetVsync(bool enabled);


		////// GETTERS!!!!!!!!

		inline uint32_t GetPositionX() { return mProperties.x; }

		inline uint32_t GetPositionY() { return mProperties.y; }

		inline uint32_t GetWidth() { return mProperties.width; }

		inline uint32_t GetHeight() { return mProperties.height; }

		inline uint8_t GetMonitor() { return mProperties.monitor; }

		inline uint8_t GetFullscreenMonitor() { return mProperties.monitorFullscreen; }

		inline FullscreenMode GetFullscreenMode() { return mProperties.fullscreenMode; }

		inline bool GetVsync() { return mProperties.vsync; }

		inline bool IsWindowOpened() { return true; }

	private:
		Window(const Window&) = delete;

		Window& operator=(const Window&) = delete;


		WindowProperties mProperties;

		void* mNativeWindow = nullptr;
	};
}

#endif