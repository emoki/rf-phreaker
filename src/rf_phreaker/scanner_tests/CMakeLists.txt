cmake_minimum_required (VERSION 2.8)

project (scanner_tests)

# scanner_tests version number.
# TODO - finish this when you have time!
set (scanner_tests_VERSION_MAJOR 1)
set (scanner_tests_VERSION_MINOR 0)
set (scanner_tests_VERSION_PATCH 0)
set (scanner_tests_VERSION_TWEAK 0)

set (scanner_tests_SRCS 
	blade_rf_controller_gtests.cpp
	byte_aligned_buffer_gtests.cpp
	mock_scanner_comm.h
	scanner_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (scanner_tests ${scanner_tests_SRCS})

target_link_libraries (scanner_tests common)
target_link_libraries (scanner_tests scanner)
#target_link_libraries (scanner bladeRF)
#target_link_libraries (scanner ipp_custom)
target_link_libraries (scanner_tests gmock)