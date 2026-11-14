set(BLAFCORE_CORE_HEADERS
	src/core/application.h
	src/core/launchArgs.h
)

set(BLAFCORE_CORE_SOURCES
	src/core/application.cpp
	src/core/launchArgs.cpp
)

source_group("Core" FILES ${BLAFCORE_CORE_HEADERS} ${BLAFCORE_CORE_SOURCES})