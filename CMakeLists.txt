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
add_subdirectory(sources/blafInput)
add_subdirectory(sources/blafRender)

add_library(BLAF INTERFACE)

if (MSVC)
	target_compile_options(BLAF INTERFACE /utf-8)
endif()

target_link_libraries(BLAF INTERFACE blafCore)
target_link_libraries(BLAF INTERFACE blafDebug)
target_link_libraries(BLAF INTERFACE blafInput)
target_link_libraries(BLAF INTERFACE blafRender)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT blafCore)

target_include_directories(BLAF INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)