set(BLAFINPUT_INPUT_HEADERS
	src/input/input.h
	src/input/keycodes.h
	src/input/platform/keycodes_WIN32.h
	src/input/platform/keycodes_UNIX.h
)

set(BLAFINPUT_INPUT_SOURCES
	src/input/platform/input_WIN32.cpp
	src/input/platform/input_UNIX.cpp
)

source_group("Input" FILES ${BLAFINPUT_INPUT_HEADERS} ${BLAFINPUT_INPUT_SOURCES})