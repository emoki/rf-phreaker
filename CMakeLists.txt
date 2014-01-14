########################################################################################
# Installation Notes
# - Make sure to turn BUILD_SHARED_LIBS for google_mock and google_test. 
# - Set path to boost using boost_USER_PATH.


# rf_phreaker project
cmake_minimum_required (VERSION 2.8)
ENABLE_LANGUAGE(CXX)

project (rf_phreaker)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/output")

# Find boost.
set (boost_USER_PATH  "e:/bin/boost_1_54_0" CACHE STRING "Enter path to boost libraries.")
set (BOOST_ROOT "${boost_USER_PATH}")
set (Boost_USE_STATIC_LIBS        ON)
set (Boost_USE_MULTITHREADED      ON)
set (Boost_USE_STATIC_RUNTIME    ON)
find_package (Boost 1.54.0 COMPONENTS thread date_time REQUIRED)

	
# Platform specific configurations.
if (MSVC)
	set (SRC_PLATFORM_SPECIFIC "${PROJECT_SOURCE_DIR}/src/rf_phreaker/arch/win")
	
	if(MSVC_VERSION LESS 1800)
		# VC11 bug: http://code.google.com/p/googletest/issues/detail?id=408
		#          add_definition(-D_VARIADIC_MAX=10)
		#          https://github.com/anhstudios/swganh/pull/186/files
		add_definitions (/D_VARIADIC_MAX=10)
	endif()

elseif (CMAKE_COMPILER_IS_GNUCXX)
	set (SRC_PLATFORM_SPECIFIC "${PROJECT_SOURCE_DIR}/src/rf_phreaker/arch/linux")
	add_definitions (-std=c++11)

endif ()




# Include directories that are common to most, if not all, projects.
include_directories (${Boost_INCLUDE_DIRS})
include_directories (${SRC_PLATFORM_SPECIFIC})
include_directories ("${PROJECT_SOURCE_DIR}/src/")
include_directories ("${PROJECT_SOURCE_DIR}/third_party/gmock/include")
include_directories ("${PROJECT_SOURCE_DIR}/third_party/gmock/gtest/include")


add_subdirectory (third_party/gmock)
add_subdirectory (third_party/g2log/g2log)
add_subdirectory (src/rf_phreaker/common)
add_subdirectory (src/rf_phreaker/common_tests)
