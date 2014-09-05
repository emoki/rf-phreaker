

project (gps_comm_tests)

# gps_comm_tests version number.
# TODO - finish this when you have time!
set (gps_comm_tests_VERSION_MAJOR 1)
set (gps_comm_tests_VERSION_MINOR 0)
set (gps_comm_tests_VERSION_PATCH 0)
set (gps_comm_tests_VERSION_TWEAK 0)

# Set the source files.
set (gps_comm_tests_SRCS 
	gps_comm_tests.cpp
	gps_service_gtests.cpp
	nmea_parser_gtests.cpp
	origin_gps_device_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories(${libbladeRF_SOURCE_DIR}/include)	

if (WIN32)
include_directories(${bladeRF_SOURCE_DIR}/common/include/windows)	
endif ()

add_executable (gps_comm_tests ${gps_comm_tests_SRCS})

target_link_libraries (gps_comm_tests gps_comm)
target_link_libraries (gps_comm_tests gmock)
