

project (gsm_layer_3_library)

# gsm_layer_3_library version number.
# TODO - finish this when you have time!
set (gsm_layer_3_library_VERSION_MAJOR 1)
set (gsm_layer_3_library_VERSION_MINOR 0)
set (gsm_layer_3_library_VERSION_PATCH 0)
set (gsm_layer_3_library_VERSION_TWEAK 0)

file (GLOB glob_SRCS *.cpp *.h)

# Remove transaction_identifier.h/cpp from source list.
list(REMOVE_ITEM glob_SRCS "${PROJECT_SOURCE_DIR}/transaction_identifier.h" )
list(REMOVE_ITEM glob_SRCS "${PROJECT_SOURCE_DIR}/transaction_identifier.cpp")

set (gsm_layer_3_library_SRCS
	${glob_SRCS}
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (gsm_layer_3_library STATIC ${gsm_layer_3_library_SRCS})

