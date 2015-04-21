project (rf_phreaker_gui)

cmake_policy(SET CMP0020 NEW)

# rf_phreaker_gui version number.
# TODO - finish this when you have time!
set (rf_phreaker_gui_VERSION_MAJOR 1)
set (rf_phreaker_gui_VERSION_MINOR 0)
set (rf_phreaker_gui_VERSION_PATCH 0)
set (rf_phreaker_gui_VERSION_TWEAK 0)

# Set the source files.
set (rf_phreaker_gui_SRCS
	main.cpp
	ApiThreadWorker.h
	ApiTypes.h
	Api.cpp
	Api.h
	ApiPlugin.h
	Base.h
	ChannelFreq.h
	CollectionInfo.h
	CollectionInfoList.cpp
	CollectionInfoList.h
	CollectionInfoSearch.cpp
	CollectionInfoSearch.h
	Device.h
	Events.h
	Gps.h
	Gsm.h
	Lte.h
	Sweep.h
	Utility.h
	Wcdma.h

	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

set (rf_phreaker_gui_QMLS
	ChannelList.qml
	DevicePage.qml
	main.qml
	SuggestionTextField.qml
	SuggestionView.qml)

set (rf_phreaker_gui_QRCS
	qml.qrc)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)

add_executable (rf_phreaker_gui  ${rf_phreaker_gui_SRCS} ${rf_phreaker_gui_QMLS} ${rf_phreaker_gui_QRCS})

target_link_libraries (rf_phreaker_gui Qt5::Core)
target_link_libraries (rf_phreaker_gui Qt5::Widgets)
target_link_libraries (rf_phreaker_gui Qt5::Quick)
target_link_libraries (rf_phreaker_gui rf_phreaker_api)

