

project (scanner_tests)

# scanner_tests version number.
# TODO - finish this when you have time!
set (scanner_tests_VERSION_MAJOR 1)
set (scanner_tests_VERSION_MINOR 0)
set (scanner_tests_VERSION_PATCH 0)
set (scanner_tests_VERSION_TWEAK 0)

set (scanner_tests_SRCS 
	blade_rf_controller_gtests.cpp
	byte_aligned_buffer_gtests.cpp
	cali_holder.h
	calibration_gtests.cpp
	eeprom_gtests.cpp
	mock_scanner_comm.h
	measurement_info_gtests.cpp
	measurement_info_serialization_gtests.cpp
	scanner_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories(${libbladeRF_SOURCE_DIR}/include)	
	
add_executable (scanner_tests ${scanner_tests_SRCS})

target_link_libraries (scanner_tests scanner)
target_link_libraries (scanner_tests gmock)
target_link_libraries (scanner_tests ${TBB_LIBRARY})
target_link_libraries (scanner_tests ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_TIMER_LIBRARY}
                                        ${Boost_CHRONO_LIBRARY})
