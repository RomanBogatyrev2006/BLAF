add_library(blafDebug STATIC
	${BLAFDEBUG_HEADERS}
	${BLAFDEBUG_SOURCES}
)

set_property(TARGET blafDebug PROPERTY FOLDER "Debug")

target_compile_features(blafDebug PUBLIC cxx_std_17)

target_include_directories(blafDebug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(blafDebug PUBLIC blafPch)