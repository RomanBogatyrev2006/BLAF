add_library(blafDebug STATIC
	${BLAFDEBUG_HEADERS}
	${BLAFDEBUG_SOURCES}
)

set_property(TARGET blafDebug PROPERTY FOLDER "Debug")

target_compile_features(blafDebug PUBLIC cxx_std_17)

target_include_directories(blafDebug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (WIN32)
	target_compile_definitions(blafDebug PRIVATE UNICODE _UNICODE)
endif()
if (MSVC)
	target_compile_definitions(blafDebug PRIVATE /utf-8)
endif()

target_link_libraries(blafDebug PUBLIC blafCore)
target_link_libraries(blafDebug PUBLIC blafPch)