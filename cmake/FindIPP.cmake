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

# Find header file dir
find_path(IPP_INCLUDE_DIR ipp.h
    PATHS ${IPP_ROOT}/ipp/include)

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
	set(IPP_LIB_ARCH_PATH "/ipp/lib/intel64/")
	set(IPP_COMPILER_ARCH_PATH "/compiler/lib/intel64/")
else()
	set(IPP_LIB_ARCH_PATH "/ipp/lib/ia32/")
	set(IPP_COMPILER_ARCH_PATH "/compiler/lib/ia32/")
endif()

macro(find_ipp_library IPP_COMPONENT)
  string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)

  # Unset the libraries so that we can reconfigure using different arch if needed.
  unset (IPP_LIB_${IPP_COMPONENT} CACHE)
  
  find_library(IPP_LIB_${IPP_COMPONENT} ipp${IPP_COMPONENT_LOWER}${IPP_LIBNAME_SUFFIX}
               PATHS "${IPP_ROOT}${IPP_LIB_ARCH_PATH}")
endmacro()

macro(find_ipp_specific_compiler_lib IPP_COMPONENT)
	string(TOLOWER ${IPP_COMPONENT} IPP_COMPONENT_LOWER)

	# Unset the libraries so that we can reconfigure using different arch if needed.
	unset (IPP_COMPILER_${IPP_COMPONENT} CACHE)
	find_library(IPP_COMPILER_${IPP_COMPONENT} ${IPP_COMPONENT_LOWER}${CMAKE_FIND_LIBRARY_SUFFIXES}
				PATHS "${IPP_ROOT}${IPP_COMPILER_ARCH_PATH}")
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


# Not currently used.
if(0)
	find_ipp_specific_compiler_lib(LIBBFP754)
	find_ipp_specific_compiler_lib(LIBDECIMAL)
	find_ipp_specific_compiler_lib(LIBIMF)
	find_ipp_specific_compiler_lib(LIBIOMP5)
	find_ipp_specific_compiler_lib(LIBIOMPSTUBS5)
	find_ipp_specific_compiler_lib(LIBIRC)	
	find_ipp_specific_compiler_lib(LIBIRNG)
	find_ipp_specific_compiler_lib(LIBMATMUL)
	find_ipp_specific_compiler_lib(LIBPDBX)
	find_ipp_specific_compiler_lib(LIBPDBXINST)
	find_ipp_specific_compiler_lib(LIBSVML)

	set(IPP_LIBRARY ${IPP_LIBRARY}
		${IPP_COMPILER_LIBBFP754}
		${IPP_COMPILER_LIBDECIMAL}
		${IPP_COMPILER_LIBIMF}
		${IPP_COMPILER_LIBIOMP5}
		${IPP_COMPILER_LIBIOMPSTUBS5}
		${IPP_COMPILER_LIBIRC}
		${IPP_COMPILER_LIBIRNG}
		${IPP_COMPILER_LIBMATMUL}
		${IPP_COMPILER_LIBPDBX}
		${IPP_COMPILER_LIBPDBXINST}
		${IPP_COMPILER_SVML})
endif()


set(IPP_LIBRARY
#    ${IPP_LIB_AC}
#    ${IPP_LIB_CC}
#    ${IPP_LIB_CH}
#    ${IPP_LIB_CP}
#    ${IPP_LIB_CV}
#    ${IPP_LIB_DC}
#    ${IPP_LIB_DI}
#    ${IPP_LIB_GEN}
#    ${IPP_LIB_I}
#    ${IPP_LIB_J}
#    ${IPP_LIB_R}
#    ${IPP_LIB_M}
    ${IPP_LIB_S}
#    ${IPP_LIB_SC}
#    ${IPP_LIB_SR}
#    ${IPP_LIB_VC}
    ${IPP_LIB_VM}
    ${IPP_LIB_CORE})

set(CMAKE_FIND_LIBRARY_SUFFIXES ${_IPP_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})

find_package_handle_standard_args(IPP DEFAULT_MSG
    IPP_INCLUDE_DIR IPP_LIBRARY)

if (IPP_FOUND)
    set(IPP_INCLUDE_DIRS ${IPP_INCLUDE_DIR})
    set(IPP_LIBRARIES ${IPP_LIBRARY})
endif()
