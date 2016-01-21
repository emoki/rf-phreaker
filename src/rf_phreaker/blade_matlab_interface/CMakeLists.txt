

project (blade_matlab_interface)

# blade_matlab_interface version number.
# TODO - finish this when you have time!
set (blade_matlab_interface_VERSION_MAJOR 1)
set (blade_matlab_interface_VERSION_MINOR 0)
set (blade_matlab_interface_VERSION_PATCH 0)
set (blade_matlab_interface_VERSION_TWEAK 0)

# Set the source files.
set (blade_matlab_interface_SRCS 
	blade_matlab_interface.cpp
	blade_matlab_interface.h
	matlab_interface_helper.h
	../cappeen/cappeen_license.cpp
	../cappeen/cappeen_license.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_definitions (/DBUILDING_DLL)

add_library (blade_matlab_interface SHARED ${blade_matlab_interface_SRCS})

target_link_libraries (blade_matlab_interface scanner)
