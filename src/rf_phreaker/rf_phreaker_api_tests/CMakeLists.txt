project (rf_phreaker_api_tests)

# rf_phreaker_api_tests version number.
# TODO - finish this when you have time!
set (rf_phreaker_api_tests_VERSION_MAJOR 1)
set (rf_phreaker_api_tests_VERSION_MINOR 0)
set (rf_phreaker_api_tests_VERSION_PATCH 0)
set (rf_phreaker_api_tests_VERSION_TWEAK 0)

# Set the source files.
set (rf_phreaker_api_tests_SRCS 
	output.h
	rf_phreaker_api_gtests.cpp
	rf_phreaker_api_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_executable (rf_phreaker_api_tests  ${rf_phreaker_api_tests_SRCS})

target_link_libraries (rf_phreaker_api_tests rf_phreaker_api)
target_link_libraries (rf_phreaker_api_tests gmock)