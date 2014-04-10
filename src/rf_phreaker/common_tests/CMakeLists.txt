

project (common_tests)

# common_tests version number.
# TODO - finish this when you have time!
set (common_tests_VERSION_MAJOR 1)
set (common_tests_VERSION_MINOR 0)
set (common_tests_VERSION_PATCH 0)
set (common_tests_VERSION_TWEAK 0)

set (common_tests_SRCS 
	common_tests.cpp
	test_operating_band_range_specifier.cpp
	channel_conversion_gtests.cpp
	raw_signal_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (common_tests ${common_tests_SRCS})

target_link_libraries (common_tests common)
target_link_libraries (common_tests gmock)

# For some reason, cmake wasn't adding boost libraries to this project
# so we're adding them manually.  Revist later after upgrading cmake.
target_link_libraries (common_tests ${Boost_LIBRARIES}) 