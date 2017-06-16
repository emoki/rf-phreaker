

project (layer_3_common_tests)

# layer_3_common_tests version number.
# TODO - finish this when you have time!
set (layer_3_common_tests_VERSION_MAJOR 1)
set (layer_3_common_tests_VERSION_MINOR 0)
set (layer_3_common_tests_VERSION_PATCH 0)
set (layer_3_common_tests_VERSION_TWEAK 0)

set (layer_3_common_tests_SRCS 
	aggregate_tests.h
	layer_3_common_tests.cpp
	test_uint16_string.cpp
	test_uint16_string.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (layer_3_common_tests ${layer_3_common_tests_SRCS})

target_link_libraries (layer_3_common_tests layer_3_common)
target_link_libraries (layer_3_common_tests gmock)