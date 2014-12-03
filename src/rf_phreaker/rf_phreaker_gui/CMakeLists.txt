project (rf_phreaker_gui)

# rf_phreaker_gui version number.
# TODO - finish this when you have time!
set (rf_phreaker_gui_VERSION_MAJOR 1)
set (rf_phreaker_gui_VERSION_MINOR 0)
set (rf_phreaker_gui_VERSION_PATCH 0)
set (rf_phreaker_gui_VERSION_TWEAK 0)

# Set the source files.
set (rf_phreaker_gui_SRCS 
	rf_phreaker_gui.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp

find_package(Qt5 COMPONENTS Quick Core QuickCompilerRuntime)

#qtquick_compiler_add_resources(RESOURCES example.qrc)

add_executable (rf_phreaker_gui  ${rf_phreaker_gui_SRCS} ${RESOURCES})

qt5_use_modules(rf_phreaker_gui Quick Core QuickCompilerRuntime)

target_link_libraries (rf_phreaker_gui rf_phreaker_api)
