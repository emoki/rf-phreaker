cmake_minimum_required (VERSION 2.8)

project (scanner)

# scanner version number.
# TODO - finish this when you have time!
set (scanner_VERSION_MAJOR 1)
set (scanner_VERSION_MINOR 0)
set (scanner_VERSION_PATCH 0)
set (scanner_VERSION_TWEAK 0)

# Set the source files.
set (scanner_SRCS 
	blade_rf_controller.cpp
	blade_rf_controller.h
	byte_aligned_buffer.h
	comm_blade_rf.h
	comm_info.h
	lms_defines.h
	lms_utilities.h
	measurement_info.h
        rf_switch_conversion.cpp
        rf_switch_conversion.h
	sampling_rate_conversion.cpp
	sampling_rate_conversion.h
	scanner.h
	scanner_blade_rf.cpp
	scanner_blade_rf.h
	scanner_blade_rf_impl.h
	scanner_controller_interface.h
	scanner_types.h
	scanner_utility.h
	time_samples_conversion.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories(${libbladeRF_SOURCE_DIR}/include)	

if (WIN32)
include_directories(${bladeRF_SOURCE_DIR}/common/include/windows)	
endif ()

add_library (scanner STATIC ${scanner_SRCS})

target_link_libraries (scanner common)
target_link_libraries (scanner libbladerf_shared)
target_link_libraries (scanner ipp_custom)
target_link_libraries (scanner optimized ${TBB_LIBRARY_RELEASE} debug ${TBB_LIBRARY_DEBUG})
