

project (fir_filter_tests)

# fir_filter_tests version number.
# TODO - finish this when you have time!
set (fir_filter_tests_VERSION_MAJOR 1)
set (fir_filter_tests_VERSION_MINOR 0)
set (fir_filter_tests_VERSION_PATCH 0)
set (fir_filter_tests_VERSION_TWEAK 0)

set (fir_filter_tests_SRCS 
	fir_filter_tests.cpp
	filter_specs_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (fir_filter_tests ${fir_filter_tests_SRCS})

target_link_libraries (fir_filter_tests fir_filter)
target_link_libraries (fir_filter_tests ipp_custom)
target_link_libraries (fir_filter_tests gmock)