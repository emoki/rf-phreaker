cmake_minimum_required (VERSION 2.8)

project (common)

# common version number.
# TODO - finish this when you have time!
set (common_VERSION_MAJOR 1)
set (common_VERSION_MINOR 0)
set (common_VERSION_PATCH 0)
set (common_VERSION_TWEAK 0)

# Set the source files.
set (common_SRCS 
		active_object.h
		benchmark.h
		common_types.h
		common_utility.h
		concurrent.h
		config_file.cpp
		config_file.h
		exception_types.h
		log.h
		measurements.h
		monitor_object.h
		operating_band_range_specifier.h
		operating_band_range_specifier.cpp
		${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (common STATIC ${common_SRCS})