project (cappeen)

# cappeen version number.
# TODO - finish this when you have time!
set (cappeen_VERSION_MAJOR 1)
set (cappeen_VERSION_MINOR 0)
set (cappeen_VERSION_PATCH 0)
set (cappeen_VERSION_TWEAK 0)

# Set the source files.
set (cappeen_SRCS 
	beagle_defines.h
	cappeen.cpp
	cappeen.h
	cappeen_delegate.h
	cappeen_impl.cpp
	cappeen_impl.h
	cappeen_license.cpp
	cappeen_license.h
	operating_band_conversion.h
	rf_phreaker_wrappers.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (cappeen SHARED ${cappeen_SRCS})

target_link_libraries (cappeen processing)
target_link_libraries (cappeen qt_specific)
target_link_libraries (cappeen hash_utility)
target_link_libraries (cappeen Qt5::Core)
