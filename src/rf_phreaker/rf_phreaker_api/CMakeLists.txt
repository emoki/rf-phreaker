project (rf_phreaker_api)

# rf_phreaker_api version number.
# TODO - finish this when you have time!
set (rf_phreaker_api_VERSION_MAJOR 1)
set (rf_phreaker_api_VERSION_MINOR 0)
set (rf_phreaker_api_VERSION_PATCH 0)
set (rf_phreaker_api_VERSION_TWEAK 0)

# Set the source files.
set (rf_phreaker_api_SRCS 
	rf_phreaker_api.cpp
	rf_phreaker_api.h
	rf_phreaker_api_converter.h
	rf_phreaker_impl.cpp
	rf_phreaker_impl.h
	measurement_io.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (rf_phreaker_api SHARED ${rf_phreaker_api_SRCS})

target_link_libraries (rf_phreaker_api processing)
target_link_libraries (rf_phreaker_api qt_specific)
