cmake_minimum_required (VERSION 2.8)

project (qt_specific)

# qt_specific version number.
# TODO - finish this when you have time!
set (qt_specific_VERSION_MAJOR 1)
set (qt_specific_VERSION_MINOR 0)
set (qt_specific_VERSION_PATCH 0)
set (qt_specific_VERSION_TWEAK 0)

# Set the source files.
set (qt_specific_SRCS 
	settings_io.cpp
	settings_io.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)


add_library (qt_specific STATIC ${qt_specific_SRCS})

target_link_libraries (qt_specific common)
target_link_libraries (qt_specific Qt5::Core)
