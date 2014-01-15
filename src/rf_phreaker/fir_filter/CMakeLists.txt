cmake_minimum_required (VERSION 2.8)

project (fir_filter)

# fir_filter version number.
# TODO - finish this when you have time!
set (fir_filter_VERSION_MAJOR 1)
set (fir_filter_VERSION_MINOR 0)
set (fir_filter_VERSION_PATCH 0)
set (fir_filter_VERSION_TWEAK 0)

# Set the source files.
set (fir_filter_SRCS 
		filter_specs.h
		fir_filter.cpp
		fir_filter.h
		fir_filter_impl.cpp
		fir_filter_impl.h
		resampling_filter_impl.h
		${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (fir_filter STATIC ${fir_filter_SRCS})

target_link_libraries (fir_filter common)