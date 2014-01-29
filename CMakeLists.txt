########################################################################################
# Installation Notes
# Make sure to turn BUILD_SHARED_LIBS for google_mock and google_test. 
# Specify the path to boost libraries using boost_USER_PATH. (apt-get or www.boost.org) 
# QT 5.2 should be installed from www.qt-project.org.
# IPP 7 or 8 does not have to be installed, however you need to set IPP_ROOT appropriately.  Look to gonzales/users/public/public documents/installations/intel ipp'. 
# Windows specific -
# IP
# Ubuntu Environment Setup -----------
# Use Nuand wiki on github for more bladeRF specific setup.
# sudo apt-get install build-essential cmake libncurses5-dev libtecla1 libtecla1-dev pkg-config git wget libudev-dev
# build libusbx manually and install (Note: configuration and build cannot occur in softlink? external drive? 
# 
# CMake Configuration
# Be sure to check USE_IPP_64_ARCH_LIBS if building for 64 architecture. 



# rf_phreaker project
cmake_minimum_required (VERSION 2.8)
ENABLE_LANGUAGE(CXX)

include(ExternalProject)

project (rf_phreaker)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/output")

# Find TBB.
if (MSVC)
	set (TBB_DEFAULT_INSTALL_DIR "${rf_phreaker_SOURCE_DIR}/third_party/tbb-win" CACHE PATH "Folder contains TBB")
else ()
	set (TBB_DEFAULT_INSTALL_DIR "${rf_phreaker_SOURCE_DIR}/third_party/tbb-linux" CACHE PATH "Folder contains TBB")
endif ()
find_package(TBB REQUIRED)

# Find IPP.
if (MSVC)
	set (IPP_ROOT "C:/Program Files (x86)/Intel/Composer XE" CACHE PATH "Folder contains IPP")
else()
	set (IPP_ROOT "${rf_phreaker_SOURCE_DIR}/third_party/ipp_linux" CACHE PATH "Folder contains IPP")
endif()
set (USE_IPP_64_ARCH_LIBS OFF CACHE BOOL "Should we link to IPP 64 bit?")
set (IPP_STATIC true)
find_package (IPP REQUIRED)


# Find boost.
set (boost_USER_PATH  "e:/bin/boost_1_54_0" CACHE STRING "Enter path to boost libraries.")
set (BOOST_ROOT "${boost_USER_PATH}")
set (Boost_USE_STATIC_LIBS        ON)
set (Boost_USE_MULTITHREADED      ON)
set (Boost_USE_STATIC_RUNTIME    OFF)
find_package (Boost 1.54.0 COMPONENTS system filesystem thread date_time timer chrono REQUIRED)
	

# MSVC configurations.
if (MSVC)
	set (SRC_PLATFORM_SPECIFIC "${PROJECT_SOURCE_DIR}/src/rf_phreaker/arch/win")
	
	if(MSVC_VERSION LESS 1800)
		# VC11 bug: http://code.google.com/p/googletest/issues/detail?id=408
		#          add_definition(-D_VARIADIC_MAX=10)
		#          https://github.com/anhstudios/swganh/pull/186/files
		add_definitions (/D_VARIADIC_MAX=10)
		add_definitions (/wd4996)
	endif()
endif()


# GCC configurations.
if (CMAKE_COMPILER_IS_GNUCXX)
	set (SRC_PLATFORM_SPECIFIC "${PROJECT_SOURCE_DIR}/src/rf_phreaker/arch/linux")
	add_definitions (-std=c++11) # Enable C++11!
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wno-unused-parameter)
	add_definitions(-Wno-deprecated-declarations) # Use until we change IPP deprecated functions.
	add_definitions(-fPIC) # Use because we want the libraries to be location independent.
endif ()


# Include directories that are common to most, if not all, projects.
include_directories (${Boost_INCLUDE_DIRS})
include_directories (${SRC_PLATFORM_SPECIFIC})
include_directories ("${PROJECT_SOURCE_DIR}/src/")
include_directories ("${PROJECT_SOURCE_DIR}/third_party/gmock/include")
include_directories ("${PROJECT_SOURCE_DIR}/third_party/gtest/include")
include_directories (${IPP_INCLUDE_DIRS})
include_directories (${TBB_INCLUDE_DIRS})

add_subdirectory (third_party/gmock)
#add_subdirectory (third_party/gtest) #gtest is automatically added by gmock
add_subdirectory (third_party/g2log/g2log)
add_subdirectory (third_party/bladerf/host)
add_subdirectory (src/rf_phreaker/common)
add_subdirectory (src/rf_phreaker/common_tests)
add_subdirectory (src/rf_phreaker/fir_filter)
add_subdirectory (src/rf_phreaker/fir_filter_tests)
add_subdirectory (src/rf_phreaker/gsm_layer_3_decoder)
add_subdirectory (src/rf_phreaker/gsm_layer_3_decoder_tests)
add_subdirectory (src/rf_phreaker/gsm_layer_3_library)
add_subdirectory (src/rf_phreaker/ipp_custom)
add_subdirectory (src/rf_phreaker/layer_3_common)
add_subdirectory (src/rf_phreaker/layer_3_common_tests)
add_subdirectory (src/rf_phreaker/umts_rrc_asn_library)
add_subdirectory (src/rf_phreaker/umts_layer_3_decoder)
add_subdirectory (src/rf_phreaker/umts_layer_3_decoder_tests)
add_subdirectory (src/rf_phreaker/umts_analysis)
add_subdirectory (src/rf_phreaker/umts_analysis_tests)
add_subdirectory (src/rf_phreaker/lte_rrc_asn_library)
add_subdirectory (src/rf_phreaker/lte_layer_3_decoder)
add_subdirectory (src/rf_phreaker/lte_layer_3_decoder_tests)
add_subdirectory (src/rf_phreaker/scanner)
add_subdirectory (src/rf_phreaker/scanner_tests)
add_subdirectory (src/rf_phreaker/processing)
add_subdirectory (src/rf_phreaker/processing_tests)
