project (rf_phreaker_gui)

cmake_policy(SET CMP0020 NEW)

# rf_phreaker_gui version number.
# TODO - finish this when you have time!
set (rfp_VERSION_MAJOR 1 CACHE INTERNAL "rf_phreaker_gui versioning" FORCE)
set (rfp_VERSION_MINOR 4 CACHE INTERNAL "rf_phreaker_gui versioning" FORCE)
set (rfp_VERSION_PATCH 2 CACHE INTERNAL "rf_phreaker_gui versioning" FORCE)
set (rfp_VERSION_TWEAK 0 CACHE INTERNAL "rf_phreaker_gui versioning" FORCE)

set (rf_phreaker_gui_VERSION_MAJOR rfp_VERSION_MAJOR)
set (rf_phreaker_gui_VERSION_MINOR rfp_VERSION_MINOR)
set (rf_phreaker_gui_VERSION_PATCH rfp_VERSION_PATCH)
set (rf_phreaker_gui_VERSION_TWEAK rfp_VERSION_TWEAK)

# Set the source files.
set (rf_phreaker_gui_SRCS
	main.cpp
	ApiMessage.h
	ApiThreadWorker.h
	ApiTypes.h
	Api.cpp
	Api.h
	ApiPlugin.h
	Base.h
	ChannelFreq.h
	CollectionInfo.h
	CollectionInfoList.h
	CollectionInfoSearch.cpp
	CollectionInfoSearch.h
	Cw.h
	Events.h
	FileSaveDialog.cpp
	FileSaveDialog.h
	FreqLimits.h
	Gps.h
	Gsm.h
	IO.h
	Lte.h
	MarbleHelper.h
	MarbleManager.h
	MarbleProxyModel.h
	MarbleLayerManager.cpp
	MarbleLayerManager.h
	MeasurementIndex.h
	MeasurementModel.h
	MessageHandler.cpp
	MessageHandler.h
	ModelGroup.h
	ProxyMeasurementModel.h
	RawLayer3.h
	RawLayer3Model.h
	RpDevice.h
	RpPositionProviderPlugin.cpp
	RpPositionProviderPlugin.h
	Serialization.h
	Settings.cpp
	Settings.h
	SettingsIO.cpp
	SettingsIO.h
	SpectrumManager.h
	SpectrumModel.h
	Spectrum3d.h
	Stats.h
	Sweep.h
	Utility.h
	Wcdma.h

	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

set (rf_phreaker_gui_QMLS
	BarChart.qml
	ChannelBarLine.qml
	ChannelBarLines.qml
	ChannelList.qml
	ChannelSweepLine.qml
	ChannelSweepLines.qml
	MarblePlacemarkList.qml
	MaterialCard.qml
	MaterialDashboardPage.qml
	MaterialExpansionButton.qml
	MaterialHeaderDelegate.qml
	MaterialItemDelegate.qml
	MaterialMain.qml
	MaterialMarblePlacemarkList.qml
	MaterialMeasurementsPage.qml
	MaterialMeasurementTable.qml
	MaterialMenuTableView.qml
	MaterialNavigationPage.qml
	MaterialOpenScannerDialog.qml
	MaterialRowDelegate.qml
	MaterialScanConfigurationPage.qml
	MaterialScanList.qml
	MaterialScannerInfoPage.qml
	MaterialSettingsPage.qml
	MaterialStateMachine.qml
	MaterialTabbedNavigationDrawerPage.qml
	MaterialToggleButton.qml
	OverviewChart.qml
	OverviewChartSweepChannel.qml
	PositionMarker.qml
	SelectScannerWindow.qml
	SuggestionTextField.qml
	SuggestionView.qml
	SweepLine.qml
	SweepLines.qml
	qtlabscontrols.conf
	)

set (qt_VERSION "5.9.0")
set (qt_PRIVATE_GUI "${qt_INSTALL_PATH}/include/QtGui/${qt_VERSION}" CACHE STRING "Path to private QT GUI.")
set (qt_PRIVATE_CORE "${qt_INSTALL_PATH}/include/QtCore/${qt_VERSION}" CACHE STRING "Path to private QT Core.")
set (qt_PRIVATE_GUIP "${qt_INSTALL_PATH}/include/QtGui/${qt_VERSION}/QtGui" CACHE STRING "Path to private QT GUI.")
set (qt_PRIVATE_COREP "${qt_INSTALL_PATH}/include/QtCore/${qt_VERSION}/QtCore" CACHE STRING "Path to private QT Core.")

include_directories (${qt_PRIVATE_GUI})
include_directories (${qt_PRIVATE_CORE})
include_directories (${qt_PRIVATE_GUIP})
include_directories (${qt_PRIVATE_COREP})
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/blendings)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/cloudsync)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/declarative)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/data)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/graphicsitem)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/scene)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/handlers)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/handlers/kml)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/handlers/dgml)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/geodata/parser)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/graphicsview)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/htmlfeatures)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/layers)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/osm)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/projections)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/routing)
include_directories (${CMAKE_SOURCE_DIR}/third_party/marble/src/lib/marble/webpopup)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)

set (AUTOGEN_TARGET_DEPENDS ${rf_phreaker_gui_SRCS})

set (rf_phreaker_gui_MAIN_QRC
	rf_phreaker.qrc
	${PROJECT_SOURCE_DIR}/icons/icons.qrc
)

#${rf_phreaker_gui_QMLS}
add_executable (rf_phreaker_gui  WIN32 ${rf_phreaker_gui_SRCS} ${rf_phreaker_gui_MAIN_QRC})

target_link_libraries (rf_phreaker_gui Qt5::Core)
target_link_libraries (rf_phreaker_gui Qt5::Gui)
target_link_libraries (rf_phreaker_gui Qt5::Widgets)
target_link_libraries (rf_phreaker_gui Qt5::Quick)
target_link_libraries (rf_phreaker_gui Qt5::DataVisualization)
target_link_libraries (rf_phreaker_gui Qt5::Charts)
target_link_libraries (rf_phreaker_gui rf_phreaker_api)
target_link_libraries (rf_phreaker_gui gsm_layer_3_decoder)
target_link_libraries (rf_phreaker_gui umts_layer_3_decoder)
target_link_libraries (rf_phreaker_gui lte_layer_3_decoder)

# Marble libraries should be built and placed in the output directory
if(MSVC)
  add_definitions(-D_USE_MATH_DEFINES=1)
endif(MSVC)

target_link_libraries (rf_phreaker_gui 
	debug ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marblewidget-qt5d.lib
	optimized ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marblewidget-qt5.lib
)
target_link_libraries (rf_phreaker_gui 
	debug ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marbledeclaratived.lib 
	optimized ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marbledeclarative.lib
)
target_link_libraries (rf_phreaker_gui 
	debug ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/materiald.lib 
	optimized ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/material.lib
)

add_custom_target(rf_phreaker_gui_copy_dependencies)
find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${qt_INSTALL_PATH} ENV qt_INSTALL_PATH PATH_SUFFIXES bin)
if(NOT EXISTS ${WINDEPLOYQT_EXECUTABLE})
	message(SEND_ERROR "Unable to find windeployqt.  Search path: ${qt_INSTALL_PATH}")
endif()
add_custom_command(TARGET rf_phreaker_gui_copy_dependencies POST_BUILD COMMAND ${WINDEPLOYQT_EXECUTABLE} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/rf_phreaker_gui.exe 
	--$<$<CONFIG:debug>:debug>$<$<NOT:$<CONFIG:debug>>:release> 
	--qmldir ${CMAKE_SOURCE_DIR}/src/rf_phreaker/rf_phreaker_gui
	--xml
	WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}
)

