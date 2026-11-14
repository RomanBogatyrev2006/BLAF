set(BLAFCORE_CORE_HEADERS
	src/core/application.h
	src/core/launchArgs.h
	src/core/entrypoint.h
	src/core/core.h
)

set(BLAFCORE_CORE_SOURCES
	src/core/application.cpp
	src/core/platform/launchArgs_UNIX.cpp
	src/core/platform/launchArgs_WIN32.cpp
)

source_group("Core" FILES ${BLAFCORE_CORE_HEADERS} ${BLAFCORE_CORE_SOURCES})