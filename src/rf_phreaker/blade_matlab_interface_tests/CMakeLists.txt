cmake_minimum_required (VERSION 2.8)

project (blade_matlab_interface_tests)

# blade_matlab_interface_tests version number.
# TODO - finish this when you have time!
set (blade_matlab_interface_tests_VERSION_MAJOR 1)
set (blade_matlab_interface_tests_VERSION_MINOR 0)
set (blade_matlab_interface_tests_VERSION_PATCH 0)
set (blade_matlab_interface_tests_VERSION_TWEAK 0)

set (blade_matlab_interface_tests_SRCS 
	blade_matlab_interface_tests.cpp
	blade_matlab_interface_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (blade_matlab_interface_tests ${blade_matlab_interface_tests_SRCS})

target_link_libraries (blade_matlab_interface_tests blade_matlab_interface)
target_link_libraries (blade_matlab_interface_tests gmock)