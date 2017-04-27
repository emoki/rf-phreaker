cmake_minimum_required(VERSION 2.8.4)
project(rf_phreaker_gui_installer)

if(WIN32)

# Generate xml files.
set(ATSYMBOL "@")
string(TIMESTAMP RELEASEDATE %Y-%m-%d)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.xml.in
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.xml
    @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/rf_phreaker/meta/package.xml.in
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/rf_phreaker/meta/package.xml
    @ONLY
)

add_custom_target(
	rf_phreaker_build_install)

set(RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR ${PROJECT_BINARY_DIR}/build)

# Add all files to cmake_binary_dir
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/config)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/config
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/config
)

add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/packages
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages
)

# Cypress USB3
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/cypress/data)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/content/cypress_usb3.7z
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/cypress/data
)

# vcredist_msvc2010_x86
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/vcredist_msvc2010_x86/data)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/content/vcredist_msvc2010_sp1_x86.7z
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/vcredist_msvc2010_x86/data
)

# vcredist_msvc2013_x86
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/vcredist_msvc2013_x86/data)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/content/2014-30-12vcredist_msvc2013_x86.7z
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/vcredist_msvc2013_x86/data
)

# RF Phreaker Directories
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data)

add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data/data)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/data
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data/data
)

# RF Phreaker Content Files
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/fpga_loads/fpga_load.rbf
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/content/gui.ini
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/content/rf_phreaker_api.ini
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)

# RF Phreaker EXE Files
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/rf_phreaker_gui.exe
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)

# RF Phreaker DLL Files
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/astro.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
		)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/bladeRF.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/common.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/fir_filter.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/g3logger_shared.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/gsm_analysis.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/gsm_layer_3_decoder.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/ipp_custom.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/lte_analysis.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/lte_layer_3_decoder.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marbledeclarative.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/marblewidget-qt5.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/material.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/pthreadVC2.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/rf_phreaker_api.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/tbb.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/umts_analysis.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/umts_layer_3_decoder.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/zlib.dll
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)

# Add QT Dependencies
set(RF_PHREAKER_INSTALL_CONFIG "release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(RF_PHREAKER_INSTALL_CONFIG "debug")
endif()
find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
if(NOT EXISTS ${WINDEPLOYQT_EXECUTABLE})
	message(SEND_ERROR "Unable to find windeployqt.  Search path: ${QTDIR}")
endif()
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${WINDEPLOYQT_EXECUTABLE} ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data/rf_phreaker_gui.exe 
	--${RF_PHREAKER_INSTALL_CONFIG} 
	--qmldir ${CMAKE_SOURCE_DIR}/src/rf_phreaker/rf_phreaker_gui
	--xml
	WORKING_DIRECTORY ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data
)

add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/packages/rf_phreaker/data/QtQuick/Controls/Styles/Material)
add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
		${qt_INSTALL_PATH}/qml/QtQuick/Controls/Styles/Material
		${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages/rf_phreaker/data/QtQuick/Controls/Styles/Material
)

# Build install file
set(BINARYCREATOR_HINTS "e:/bin/qt/qt_fi_2.0.1/bin")
find_program(QTBINARYCREATOR_EXECUTABLE NAMES binarycreator HINTS ${BINARYCREATOR_HINTS} ENV QTDIR PATH_SUFFIXES bin)
if(NOT EXISTS ${QTBINARYCREATOR_EXECUTABLE})
	message(SEND_ERROR "Unable to find binarycreator for installation of rf_phreaker_gui! Search path: ${BINARYCREATOR_HINTS}" )
else()
	add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/install)
	set(RF_PHREAKER_INSTALL_NAME ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/install/rf_phreaker_install_v${rfp_VERSION_MAJOR}.${rfp_VERSION_MINOR}.${rfp_VERSION_PATCH})
	add_custom_command(TARGET rf_phreaker_build_install POST_BUILD COMMAND ${QTBINARYCREATOR_EXECUTABLE} 
		--offline-only 
		--config ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/config/config.xml 
		--packages ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}/packages 
		${RF_PHREAKER_INSTALL_NAME}
		WORKING_DIRECTORY ${RF_PHREAKER_INSTALLER_BUILD_INSTALL_DIR}
	)
endif()


endif()
