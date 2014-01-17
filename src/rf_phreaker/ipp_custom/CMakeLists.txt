cmake_minimum_required (VERSION 2.8)

project (ipp_custom)

# ipp_custom version number.
# TODO - finish this when you have time!
set (ipp_custom_VERSION_MAJOR 1)
set (ipp_custom_VERSION_MINOR 0)
set (ipp_custom_VERSION_PATCH 0)
set (ipp_custom_VERSION_TWEAK 0)

# Set the source files.
set (ipp_custom_SRCS 
	ipp_array.h
	ipp_helper.h
	ipp_export.def
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain_ipp_custom.cpp)


add_definitions (/DBUILDING_DLL)

add_library (ipp_custom SHARED ${ipp_custom_SRCS})

# On linux we cannot export functions therefore we set the target_link to public so  
# every project that references ipp_custom will also reference the IPP libraries.
# Note the IPP libraries should be static.
if(MSVC)
	target_link_libraries (ipp_custom LINK_PRIVATE ${IPP_LIBRARIES})
else()
	target_link_libraries (ipp_custom LINK_PUBLIC ${IPP_LIBRARIES})
endif()