

project (qt_specific_tests)

cmake_policy (SET CMP0020 NEW)
	
# qt_specific_tests version number.
# TODO - finish this when you have time!
set (qt_specific_tests_VERSION_MAJOR 1)
set (qt_specific_tests_VERSION_MINOR 0)
set (qt_specific_tests_VERSION_PATCH 0)
set (qt_specific_tests_VERSION_TWEAK 0)

# Set the source files.
set (qt_specific_tests_SRCS 
	qt_specific_tests.cpp
	settings_io_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)


add_executable (qt_specific_tests ${qt_specific_tests_SRCS})

target_link_libraries (qt_specific_tests qt_specific)
target_link_libraries (qt_specific_tests gmock)