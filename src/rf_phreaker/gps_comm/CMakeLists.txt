

project (gps_comm)

# gps_comm version number.
# TODO - finish this when you have time!
set (gps_comm_VERSION_MAJOR 1)
set (gps_comm_VERSION_MINOR 0)
set (gps_comm_VERSION_PATCH 0)
set (gps_comm_VERSION_TWEAK 0)

# Set the source files.
set (gps_comm_SRCS 
	BladeContext.cpp
	BladeContext.h
	BladeDevice.cpp
	BladeDevice.h
	BladeError.cpp
	BladeError.h
	BladeRF.hpp
	Event.h
	FrontEndBoard.h
	FrontEndBoard.cpp
	gps_comm.h
	gps_comm.cpp
	gps_comm_impl.h
	GPSFix.cpp
	GPSFix.h
	GPSService.cpp
	GPSService.h
	NMEACommand.cpp
	NMEACommand.h
	NMEAParser.cpp
	NMEAParser.h
	NumberConversion.cpp
	NumberConversion.h
	GPSDevice.h
	GPSDevice.cpp	
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories(${libbladeRF_SOURCE_DIR}/include)	

if (WIN32)
include_directories(${bladeRF_SOURCE_DIR}/common/include/windows)	
endif ()

add_library (gps_comm ${gps_comm_SRCS})

target_link_libraries (gps_comm common)
target_link_libraries (gps_comm libbladerf_shared)

