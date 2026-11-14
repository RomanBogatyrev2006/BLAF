set(BLAFCORE_TIME_HEADERS
	src/time/timer.h
	src/time/fpslimit.h
)

set(BLAFCORE_TIME_SOURCES
	src/time/platform/timer_WIN32.cpp
	src/time/platform/timer_UNIX.cpp
	src/time/platform/fpslimit_WIN32.cpp
	src/time/platform/fpslimit_UNIX.cpp
)

source_group("Time" FILES ${BLAFCORE_TIME_HEADERS} ${BLAFCORE_TIME_SOURCES})