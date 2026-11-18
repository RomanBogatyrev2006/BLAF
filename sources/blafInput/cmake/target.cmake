add_library(blafInput STATIC
	${BLAFINPUT_HEADERS}
	${BLAFINPUT_SOURCES}
)

set_property(TARGET blafInput PROPERTY FOLDER "Input")

target_compile_features(blafInput PUBLIC cxx_std_17)

target_include_directories(blafInput PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (WIN32)
	target_compile_definitions(blafInput PRIVATE UNICODE _UNICODE)
endif()
if (MSVC)
	target_compile_options(blafInput PRIVATE /utf-8)
endif()

target_link_libraries(blafInput PUBLIC blafCore)
target_link_libraries(blafInput PUBLIC blafDebug)
target_link_libraries(blafInput PUBLIC blafPch)