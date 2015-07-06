

project (gsm_analysis_tests)

# gsm_analysis_tests version number.
# TODO - finish this when you have time!
set (gsm_analysis_tests_VERSION_MAJOR 1)
set (gsm_analysis_tests_VERSION_MINOR 0)
set (gsm_analysis_tests_VERSION_PATCH 0)
set (gsm_analysis_tests_VERSION_TWEAK 0)

set (gsm_analysis_tests_SRCS 
	gsm_analysis_gtests.cpp
	gsm_analysis_tests.cpp
	gsm_interface_gtests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (gsm_analysis_tests ${gsm_analysis_tests_SRCS})

target_link_libraries (gsm_analysis_tests gsm_analysis)
target_link_libraries (gsm_analysis_tests gmock)