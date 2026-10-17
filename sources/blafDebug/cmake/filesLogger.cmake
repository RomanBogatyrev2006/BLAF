set(BLAFDEBUG_LOGGER_HEADERS
	src/logger/logger.h
	src/logger/logLevels.h
	src/assert/assert.h
)

set(BLAFDEBUG_LOGGER_SOURCES
	src/logger/platform/logger_WIN32.cpp
	src/logger/platform/logger_UNIX.cpp
)

source_group("Logger" FILES ${BLAFDEBUG_LOGGER_HEADERS} ${BLAFDEBUG_LOGGER_SOURCES})