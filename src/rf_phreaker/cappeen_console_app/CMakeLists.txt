

project (cappeen_console_app)

# cappeen_console_app version number.
# TODO - finish this when you have time!
set (cappeen_console_app_VERSION_MAJOR 1)
set (cappeen_console_app_VERSION_MINOR 0)
set (cappeen_console_app_VERSION_PATCH 0)
set (cappeen_console_app_VERSION_TWEAK 0)

set (cappeen_console_app_SRCS 
	api_string.h
	beagle_io.cpp
	beagle_io.h
	cappeen_command_handler.cpp
	cappeen_command_handler.h
	cappeen_console_app.cpp
	cappeen_delegate.cpp
	cappeen_delegate.h
	cappeen_dispatcher.cpp
	cappeen_dispatcher.h
	cappeen_interface.h
	cappeen_io.cpp
	cappeen_io.h
	cappeen_utilities.cpp
	cappeen_utilities.h
	cappeen_wrapper.h
	group.h
	helper_structs.h
	simple_logger.cpp
	simple_logger.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (cappeen_console_app ${cappeen_console_app_SRCS})

target_link_libraries (cappeen_console_app cappeen)
