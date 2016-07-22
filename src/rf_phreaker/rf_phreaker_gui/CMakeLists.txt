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
	Events.h
	FileSaveDialog.cpp
	FileSaveDialog.h
	Gps.h
	Gsm.h
	IO.h
	Lte.h
	MarbleManager.h
	MarbleProxyModel.h
	MeasurementIndex.h
	MeasurementModel.h
	ModelGroup.h
	ProxyMeasurementModel.h
	RpDevice.h
	RpPositionProviderPlugin.cpp
	RpPositionProviderPlugin.h
	Serialization.h
	Settings.h
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
	CircularButton.qml
	CustomFlatButtonStyle.qml
	DataAnalysisLabel.qml
	DataAnalysisPage.qml
	DataOverviewPage.qml
	DataWorksheet.qml
	DevicePage.qml
	main.qml
	MapPage.qml
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
	MaterialStateMachine.qml
	MaterialTabbedNavigationDrawerPage.qml
	OverviewChart.qml
	PositionButton.qml
	PositionMarker.qml
	ScanConfigurationPage.qml
	ScannerPage.qml
	SelectScannerWindow.qml
	SideBarLabel.qml
	StateMachine.qml
	SuggestionTextField.qml
	SuggestionView.qml
	SweepLine.qml
	SweepLines.qml
	WorkbenchPage.qml
	qtlabscontrols.conf
	)

set (qt_PRIVATE_GUI "C:/bin/qt/5.5/msvc2013/include/QtGui/5.5.1" CACHE STRING "Path to private QT GUI.")
set (qt_PRIVATE_CORE "C:/bin/qt/5.5/msvc2013/include/QtCore/5.5.1" CACHE STRING "Path to private QT Core.")
set (qt_PRIVATE_GUIP "C:/bin/qt/5.5/msvc2013/include/QtGui/5.5.1/QtGui" CACHE STRING "Path to private QT GUI.")
set (qt_PRIVATE_COREP "C:/bin/qt/5.5/msvc2013/include/QtCore/5.5.1/QtCore" CACHE STRING "Path to private QT Core.")

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
add_executable (rf_phreaker_gui  ${rf_phreaker_gui_SRCS} ${rf_phreaker_gui_MAIN_QRC})

target_link_libraries (rf_phreaker_gui Qt5::Core)
target_link_libraries (rf_phreaker_gui Qt5::Widgets)
target_link_libraries (rf_phreaker_gui Qt5::Quick)
target_link_libraries (rf_phreaker_gui rf_phreaker_api)

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
