

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
	blade_rf_controller_async.h
	byte_aligned_buffer.h
	calibration.cpp
	calibration.h
	comm_blade_rf.h
	comm_info.h
	eeprom.h
	eeprom.cpp
	eeprom_defines.h
	gain.h
	gain_manager.h
	freq_correction_container.h
	lms_defines.h
	lms_utilities.h
	nr_interface.h
	measurement_info.h
	measurement_info_serialization.h
	rf_adjustment.h
    rf_switch_conversion.h
	scanner.h
	scanner_blade_rf.cpp
	scanner_blade_rf.h
	scanner_blade_rf_impl.h
	scanner_controller_interface.h
	scanner_types.h
	scanner_utility.h
	signal_level_calculator.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories(${libbladeRF_SOURCE_DIR}/include)	

if (WIN32)
include_directories(${bladeRF_SOURCE_DIR}/common/include/windows)	
endif ()

add_library (scanner STATIC ${scanner_SRCS})

target_link_libraries (scanner common)
target_link_libraries (scanner gps_comm)
target_link_libraries (scanner libbladerf_shared)
target_link_libraries (scanner ipp_custom)
target_link_libraries (scanner ${TBB_LIBRARY})