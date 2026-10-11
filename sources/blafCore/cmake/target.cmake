add_library(blafCore STATIC
	${BLAFCORE_HEADERS}
	${BLAFCORE_SOURCES}
)

set_property(TARGET blafCore PROPERTY FOLDER "Core")

target_compile_features(blafCore PUBLIC cxx_std_17)

target_include_directories(blafCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(blafCore PUBLIC blafDebug)
target_link_libraries(blafCore PUBLIC blafPch)