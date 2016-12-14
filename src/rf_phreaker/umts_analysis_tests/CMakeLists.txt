

project (umts_analysis_tests)

# umts_analysis_tests version number.
# TODO - finish this when you have time!
set (umts_analysis_tests_VERSION_MAJOR 1)
set (umts_analysis_tests_VERSION_MINOR 0)
set (umts_analysis_tests_VERSION_PATCH 0)
set (umts_analysis_tests_VERSION_TWEAK 0)

# Set the source files.
set (umts_analysis_tests_SRCS 
	umts_analysis_tests.cpp
	umts_analysis_gtests.cpp
	umts_measurement_container_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)


add_executable (umts_analysis_tests ${umts_analysis_tests_SRCS})

target_link_libraries (umts_analysis_tests common)
target_link_libraries (umts_analysis_tests gmock)
target_link_libraries (umts_analysis_tests umts_analysis)
