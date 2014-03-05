

project (processing_tests)

# processing_tests version number.
# TODO - finish this when you have time!
set (processing_tests_VERSION_MAJOR 1)
set (processing_tests_VERSION_MINOR 0)
set (processing_tests_VERSION_PATCH 0)
set (processing_tests_VERSION_TWEAK 0)

set (processing_tests_SRCS 
	collection_info_container_gtests.cpp
	layer_3_tracker_gtests.cpp
	processing_tests.cpp
	processing_graph_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (processing_tests ${processing_tests_SRCS})

target_link_libraries (processing_tests processing)
target_link_libraries (processing_tests gmock)
target_link_libraries (processing_tests qt_specific)
