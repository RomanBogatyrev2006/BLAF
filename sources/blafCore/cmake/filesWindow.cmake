set(BLAFCORE_WINDOW_HEADERS
	src/window/window.h
	src/window/windowProps.h
)

set(BLAFCORE_WINDOW_SOURCES
	src/window/platform/window_WIN32.cpp
	src/window/platform/window_X11.cpp
	src/window/platform/window_WAYLAND.cpp
)

source_group("Window" FILES ${BLAFCORE_WINDOW_HEADERS} ${BLAFCORE_WINDOW_SOURCES})