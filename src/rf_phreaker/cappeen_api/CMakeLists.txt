project (cappeen_api)

# cappeen_api version number.
# TODO - finish this when you have time!
set (cappeen_api_VERSION_MAJOR 1)
set (cappeen_api_VERSION_MINOR 0)
set (cappeen_api_VERSION_PATCH 0)
set (cappeen_api_VERSION_TWEAK 0)

# Set the source files.
set (cappeen_api_SRCS 
	beagle_defines.h
	cappeen_api.cpp
	cappeen_api.h
	cappeen_delegate.h
	cappeen_impl.cpp
	cappeen_impl.h
	operating_band_conversion.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (cappeen_api SHARED ${cappeen_api_SRCS})

target_link_libraries (cappeen_api processing)
target_link_libraries (cappeen_api qt_specific)
