cmake_minimum_required (VERSION 2.8)

project (umts_rrc_asn_library)

# umts_rrc_asn_library version number.
# TODO - finish this when you have time!
set (umts_rrc_asn_library_VERSION_MAJOR 1)
set (umts_rrc_asn_library_VERSION_MINOR 0)
set (umts_rrc_asn_library_VERSION_PATCH 0)
set (umts_rrc_asn_library_VERSION_TWEAK 0)

file (GLOB glob_SRCS *.c *.h)

set (umts_rrc_asn_library_SRCS
	${glob_SRCS})

if (CMAKE_COMPILER_IS_GNUCXX)
	remove_definitions (-std=c++11) 
endif ()

add_library (umts_rrc_asn_library STATIC ${umts_rrc_asn_library_SRCS})

