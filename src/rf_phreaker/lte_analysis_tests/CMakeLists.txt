

project (lte_analysis_tests)

# lte_analysis_tests version number.
# TODO - finish this when you have time!
set (lte_analysis_tests_VERSION_MAJOR 1)
set (lte_analysis_tests_VERSION_MINOR 0)
set (lte_analysis_tests_VERSION_PATCH 0)
set (lte_analysis_tests_VERSION_TWEAK 0)

# Set the source files.
set (lte_analysis_tests_SRCS 
	lte_analysis_tests.cpp
	lte_analysis_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)


add_executable (lte_analysis_tests ${lte_analysis_tests_SRCS})

target_link_libraries (lte_analysis_tests common)
target_link_libraries (lte_analysis_tests gmock)
target_link_libraries (lte_analysis_tests lte_analysis)
