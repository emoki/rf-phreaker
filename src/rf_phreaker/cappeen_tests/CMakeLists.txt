

project (cappeen_tests)

# cappeen_tests version number.
# TODO - finish this when you have time!
set (cappeen_tests_VERSION_MAJOR 1)
set (cappeen_tests_VERSION_MINOR 0)
set (cappeen_tests_VERSION_PATCH 0)
set (cappeen_tests_VERSION_TWEAK 0)

set (cappeen_tests_SRCS 
	cappeen_gtests.cpp
	cappeen_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (cappeen_tests ${cappeen_tests_SRCS})

target_link_libraries (cappeen_tests cappeen)
target_link_libraries (cappeen_tests gmock)
