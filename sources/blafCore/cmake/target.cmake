add_library(blafCore STATIC
	${BLAFCORE_HEADERS}
	${BLAFCORE_SOURCES}
)

set_property(TARGET blafCore PROPERTY FOLDER "Core")

target_compile_features(blafCore PUBLIC cxx_std_17)

target_include_directories(blafCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (WIN32)
	target_compile_definitions(blafCore PRIVATE UNICODE _UNICODE)
endif()
if (MSVC)
	target_compile_options(blafCore PRIVATE /utf-8)
endif()

target_link_libraries(blafCore PUBLIC blafRender)
target_link_libraries(blafCore PUBLIC blafDebug)
target_link_libraries(blafCore PUBLIC blafPch)