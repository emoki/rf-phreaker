# - Find Intel IPP
# Find the IPP libraries
# Options:
#
#   IPP_STATIC: true if using static linking
#   IPP_MULTI_THREADED: true if using multi-threaded static linking
#
# This module defines the following variables:
#
#   IPP_FOUND       : True if IPP_INCLUDE_DIR are found
#   IPP_INCLUDE_DIR : where to find ipp.h, etc.
#   IPP_INCLUDE_DIRS: set when IPP_INCLUDE_DIR found
#   IPP_LIBRARIES   : the library to link against.

include(FindPackageHandleStandardArgs)

if (MSVC)
	set (IPP_ROOT "${RF_PHREAKER_ROOT_PATH}/third_party/ipp_win/ipp" CACHE PATH "Folder contains IPP")
else()
	set (IPP_ROOT "${RF_PHREAKER_ROOT_PATH}/third_party/ipp_linux/ipp" CACHE PATH "Folder contains IPP")
endif()

set (USE_IPP_64_ARCH_LIBS OFF CACHE BOOL "Should we link to IPP 64 bit?")

# Find header file dir
find_path(IPP_INCLUDE_DIR ipp.h
    PATHS ${IPP_ROOT}/include)

# Find libraries

# Handle suffix
set(_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})

if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
else()
    if(IPP_STATIC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so)
    endif()
endif()

if(IPP_STATIC AND WIN32)
    set(IPP_LIBNAME_SUFFIX mt)
else()
    set(IPP_LIBNAME_SUFFIX "")
endif()

if(USE_IPP_64_ARCH_LIBS)
	set(IPP_LIB_ARCH_PATH "/lib/intel64/")
else()
	set(IPP_LIB_ARCH_PATH "/lib/ia32/")
endif()

macro(find_ipp_library IPP_COMPONENT)
  string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)

  # Unset the libraries so that we can reconfigure using different arch if needed.
  unset (IPP_LIB_${IPP_COMPONENT} CACHE)
  
  find_library(IPP_LIB_${IPP_COMPONENT} ipp${IPP_COMPONENT_LOWER}${IPP_LIBNAME_SUFFIX}
               PATHS "${IPP_ROOT}${IPP_LIB_ARCH_PATH}")
endmacro()



# IPP components
# Core
find_ipp_library(CORE)
# Audio Coding
find_ipp_library(AC)
# Color Conversion
find_ipp_library(CC)
# String Processing
find_ipp_library(CH)
# Cryptography - not within our release
#find_ipp_library(CP)
# Computer Vision
find_ipp_library(CV)
# Data Compression
find_ipp_library(DC)
# Data Integrity
find_ipp_library(DI)
# Generated Functions
find_ipp_library(GEN)
# Image Processing
find_ipp_library(I)
# Image Compression
find_ipp_library(J)
# Realistic Rendering and 3D Data Processing
find_ipp_library(R)
# Small Matrix Operations
find_ipp_library(M)
# Signal Processing
find_ipp_library(S)
# Speech Coding
find_ipp_library(SC)
# Speech Recognition - not within our release
#find_ipp_library(SR)
# Video Coding
find_ipp_library(VC)
# Vector Math
find_ipp_library(VM)

set(IPP_LIBRARY
    ${IPP_LIB_CORE}
    ${IPP_LIB_AC}
    ${IPP_LIB_CC}
    ${IPP_LIB_CH}
    ${IPP_LIB_CP}
    ${IPP_LIB_CV}
    ${IPP_LIB_DC}
    ${IPP_LIB_DI}
    ${IPP_LIB_GEN}
    ${IPP_LIB_I}
    ${IPP_LIB_J}
    ${IPP_LIB_R}
    ${IPP_LIB_M}
    ${IPP_LIB_S}
    ${IPP_LIB_SC}
    ${IPP_LIB_SR}
    ${IPP_LIB_VC}
    ${IPP_LIB_VM})

set(CMAKE_FIND_LIBRARY_SUFFIXES ${_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})

find_package_handle_standard_args(IPP DEFAULT_MSG
    IPP_INCLUDE_DIR IPP_LIBRARY)

if (IPP_FOUND)
    set(IPP_INCLUDE_DIRS ${IPP_INCLUDE_DIR})
    set(IPP_LIBRARIES ${IPP_LIBRARY})
endif()
