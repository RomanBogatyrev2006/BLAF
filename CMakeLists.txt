cmake_minimum_required(VERSION 3.20)

project(BLAF LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (WIN32)
	message(STATUS "Detected platform: Windows")
	add_compile_definitions(BLAF_TARGET_WINDOWS)
endif ()

if (UNIX)
	message(STATUS "Detected platform: Unix/Linux")
	add_compile_definitions(BLAF_TARGET_UNIX)
endif ()

add_subdirectory(sources/blafCore)
add_subdirectory(sources/blafPch)
add_subdirectory(sources/blafDebug)

add_library(BLAF INTERFACE)

target_link_libraries(BLAF INTERFACE blafCore)
target_link_libraries(BLAF INTERFACE blafDebug)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT blafCore)

target_include_directories(BLAF INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)