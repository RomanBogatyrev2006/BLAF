add_library(blafRender STATIC
	${BLAFRENDER_HEADERS}
	${BLAFRENDER_SOURCES}
)

set_property(TARGET blafRender PROPERTY FOLDER "Render")

target_compile_features(blafRender PUBLIC cxx_std_17)

target_include_directories(blafRender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (WIN32)
	target_compile_definitions(blafRender PRIVATE UNICODE _UNICODE)
endif()
if (MSVC)
	target_compile_options(blafRender PRIVATE /utf-8)
endif()

target_link_libraries(blafRender PUBLIC blafCore)
target_link_libraries(blafRender PUBLIC blafDebug)
target_link_libraries(blafRender PUBLIC blafPch)