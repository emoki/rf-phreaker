import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQml.StateMachine 1.0 as DSM
import QtQml 2.2
import Qt.labs.settings 1.0
import RfPhreaker 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("RF Phreaker")

    property color sideBarStatus: "#303f9F"
    property color sideBarColor: "lightgrey"
    property color contentColor: "white"//"#3F51B5"
    readonly property bool contentLoaded: contentLoader.item
    property int textMargins: Math.round(32 * Flat.FlatStyle.scaleFactor)
    property int menuMargins: Math.round(13 * Flat.FlatStyle.scaleFactor)
    property int sideBarWidth: 270 //Math.min(mainWindow.width, mainWindow.height) * 0.45
    property int textMenuPixelSize: 22 //Math.round(1100 * FlatStyle.scaleFactor)
    property int sideBarIconSize: 35 //Math.round(100 * FlatStyle.scaleFactor)
    property int scannerDetailsPixelSize: 14 //Math.round(100 * FlatStyle.scaleFactor)
    property ScannerPage scannerPage: Component { ScannerPage {} }
    property MapPage mapPage: Component { MapPage {} }
    property ScanConfigurationPage scanConfigurationPage: Component { ScanConfigurationPage {} }
    property DataAnalysisPage dataAnalysisPage/*: Component { DataAnalysisPage {} }*/
    property WorkbenchPage workbenchPage: Component { WorkbenchPage {} }

    onClosing: {
        console.debug("Closing main app!");
        dsmOperation.stop();
        Api.cleanUpApi();
    }

    Settings {
        id: settings
        property alias x: mainWindow.x
        property alias y: mainWindow.y
        property alias width: mainWindow.width
        property alias height: mainWindow.height
    }

    StateMachine {
        id: dsmOperation
    }

    SelectScannerWindow {
        id: selectScannerWindow
    }

    FontMetrics {
        id: fontMetrics
        font.family: Flat.FlatStyle.fontFamily
    }


    Rectangle {
        id: container
        anchors.fill: parent
        color: sideBarColor

        ColumnLayout {
            id: sideBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: textMargins / 2
            anchors.leftMargin: textMargins / 2
            //anchors.bottomMargin: textMargins / 2
            //anchors.bottom: parent.bottom
            spacing: textMargins / 2
            width: sideBarWidth
            Layout.alignment: Qt.AlignTop

            SideBarLabel {
                id: connectionStatusSideBar
                label.font.italic: true
                iconSize: sideBarIconSize * 1.2
                //pixelSize: textMenuPixelSize * 1.2
                Layout.preferredHeight: iconSize
                Layout.fillWidth: true
                states: [
                    State {
                        when: Api.connectionStatus === ApiTypes.DISCONNECTED
                        PropertyChanges {
                            target: connectionStatusSideBar;
                            text: Api.deviceStatus === ApiTypes.ERROR ? Api.connectedDevice.serialShort + " Disconnected" : "Disconnected"
                            componentIndex: 0
                            defaultImageSource: "qrc:/icons/action_help.svg"
                        }
                    },
                    State {
                        when: Api.connectionStatus === ApiTypes.CONNECTING
                        PropertyChanges {
                            target: connectionStatusSideBar;
                            text: Api.connectedDevice.serialShort + " Connecting"
                            componentIndex: 1
                        }
                    },
                    State {
                        when: Api.connectionStatus === ApiTypes.CONNECTED
                        PropertyChanges {
                            target: connectionStatusSideBar;
                            text: Api.connectedDevice.serialShort + " Connected"
                            componentIndex: 0
                            defaultImageSource: "qrc:/icons/device_usb.svg"
                        }
                    }
                ]
            }
            SideBarLabel {
                id: deviceStatusSB
                label.font.italic: true
                iconSize: sideBarIconSize * 1.2
                //pixelSize: textMenuPixelSize * 1.2
                Layout.preferredHeight: iconSize
                Layout.fillWidth: true
                text: Api.deviceStatusStr
                states: [
                    State {
                        when: Api.deviceStatus === ApiTypes.OFF
                        PropertyChanges {
                            target: deviceStatusSB;
                            activated: false
                        }
                    },
                    State {
                        when: Api.deviceStatus === ApiTypes.ERROR
                        PropertyChanges {
                            target: deviceStatusSB;
                            activated: true
                            text: "ERROR"
                            componentIndex: defaultImageIndex
                            defaultImageSource: "qrc:/icons/alert_error.svg"
                        }
                    },
                    State {
                        when: Api.deviceStatus === ApiTypes.IDLE
                        PropertyChanges {
                            target: deviceStatusSB;
                            activated: true
                            text: "IDLE"
                            componentIndex: defaultImageIndex
                            defaultImageSource: "qrc:/icons/scanning_idle.png"
                        }
                    },
                    State {
                        when: Api.deviceStatus === ApiTypes.SCANNING
                        PropertyChanges {
                            target: deviceStatusSB;
                            text: "SCANNING"
                            componentIndex: deviceStatusSB.animatedSpriteIndex
                            animatedSpriteSource: "qrc:/icons/scanning_idle.png"
                        }
                    },
                    State {
                        when: Api.deviceStatus === ApiTypes.BACKGROUND_SCANNING
                        PropertyChanges {
                            target: deviceStatusSB;
                            text: "RECORDING"
                            componentIndex: deviceStatusSB.animatedSpriteIndex
                            animatedSpriteSource: "qrc:/icons/scanning_sprite.png"
                        }
                    },
                    State {
                        when: Api.deviceStatus === ApiTypes.RECORDING
                        PropertyChanges {
                            target: deviceStatusSB;
                            text: "RECORDING"
                            componentIndex: deviceStatusSB.animatedSpriteIndex
                            animatedSpriteSource: "qrc:/icons/scanning_sprite.png"
                        }
                    }
                ]

            }
            SideBarLabel {
                label.font.italic: true
                iconSize: sideBarIconSize * 1.2
                //pixelSize: textMenuPixelSize * 1.2
                Layout.preferredHeight: iconSize
                Layout.fillWidth: true
                activated: Api.connectionStatus !== ApiTypes.DISCONNECTED && Api.connectionStatus !== ApiTypes.CONNECTING
                defaultImageSource: Api.gps.gpsLock ? "qrc:/icons/device_gps_fixed.svg" : "qrc:/icons/device_gps_not_fixed.svg";
                text: Api.gps.gpsLock ? "Position Locked" : "Position Not Locked"
            }
            RowLayout {
                Layout.fillWidth: true
                Button {
                    id: stopButton
                    text: "Stop"
                    Layout.fillWidth: true
                    style: CustomFlatButtonStyle { textPixelSize: 25}
                    enabled: Api.deviceStatus === ApiTypes.SCANNING || Api.deviceStatus === ApiTypes.RECORDING
                    onClicked: {
                        Api.stopCollection();
                        Api.closeCollectionFile();
                    }
                }
                Button {
                    id: recordButton
                    text: "Record"
                    Layout.fillWidth: true
                    enabled: Api.deviceStatus === ApiTypes.IDLE && Api.scanList.size > 0
                    onClicked: {
                        startCollectionDialog.filename = "collection_data_" +
                                Qt.formatDateTime(new Date(), "yyyy-MMM-dd_hh-mm-ss");
                        startCollectionDialog.open();
                    }
                    style: CustomFlatButtonStyle { textPixelSize: 25}

                    StatusIndicator {
                        id: recordIndicator
                        active: Api.deviceStatus === ApiTypes.RECORDING
                        anchors.left: parent.left
                        anchors.leftMargin: Math.max(6, Math.round(recordButton.text.height * 0.4))
                        anchors.verticalCenter: parent.verticalCenter
                        rotation: 90
                    }
                }
            }
            Rectangle {
                border.width: 2
                border.color: "black"
                Layout.fillWidth: true
                height: 2
            }
            SideBarLabel {
                Layout.preferredHeight: sideBarIconSize
                Layout.fillWidth: true
                defaultImageSource: "qrc:/icons/hardware_developer_board.svg"
                text: "Scanner"
                MouseArea {
                    anchors.fill: parent
                    onClicked: contentLoader.sourceComponent = scannerPage;
                }
            }
            Rectangle {
                border.width: 2
                border.color: "black"
                Layout.fillWidth: true
                height: 2
            }
            SideBarLabel {
                id: scanConfiguration
                Layout.preferredHeight: sideBarIconSize
                Layout.fillWidth: true
                text: "Scan Configuration"
                defaultImageSource: "qrc:/icons/hardware_developer_board.svg"
                MouseArea {
                    anchors.fill: parent
                    onClicked: contentLoader.sourceComponent = scanConfigurationPage;
                }
            }
            ListView {
                id: smallChannelView
                Layout.minimumHeight: 0
                Layout.maximumHeight: scannerDetailsPixelSize * rowCount
                Layout.preferredHeight: scannerDetailsPixelSize * rowCount
                Layout.fillHeight: true;
                Layout.fillWidth: true
                property int rowCount: Api.scanList.size
                property var scanList: Api.scanList
                model: scanList.list
                delegate: Row {
                    id: smallChannelViewDelegate
                    width: smallChannelView.width
                    property CollectionInfo ci: smallChannelView.scanList.at(index)
                    Text {
                        width: smallChannelViewDelegate.width * .2
                        horizontalAlignment: Text.AlignRight
                        text: ci.isSweep ? "Sweeping" : "Full Scan";
                    }
                    Text {
                        width: smallChannelViewDelegate.width * .4
                        horizontalAlignment: Text.AlignHCenter
                        text: ci.isSweep ? ci.band : ci.channels;
                    }
                    Text {
                        width: smallChannelViewDelegate.width * .4
                        horizontalAlignment: Text.AlignHCenter
                        text: ci.freqs;
                    }
                }
            }
            Rectangle {
                border.width: 2
                border.color: "black"
                Layout.fillWidth: true
                height: 2
            }
            SideBarLabel {
                Layout.preferredHeight: sideBarIconSize
                Layout.fillWidth: true
                defaultImageSource: "qrc:/icons/editor_insert_chart.svg"
                text: "Data View"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        //dataAnalysisPage.loadAnalysisSelection();
                        contentLoader.sourceComponent = Qt.createComponent("DataAnalysisPage.qml");
                    }
                }
            }
            Rectangle {
                border.width: 2
                border.color: "black"
                Layout.fillWidth: true
                height: 2
            }
            SideBarLabel {
                Layout.preferredHeight: sideBarIconSize
                Layout.fillWidth: true
                defaultImageSource: "qrc:/icons/maps_map.svg"
                text: "Navigation"
                MouseArea {
                    anchors.fill: parent
                    onClicked: contentLoader.sourceComponent = mapPage;
                }
            }
            Rectangle {
                border.width: 2
                border.color: "black"
                Layout.fillWidth: true
                height: 2
            }
            SideBarLabel {
                id: testBenchIcon
                Layout.preferredHeight: sideBarIconSize
                Layout.fillWidth: true
                defaultImageSource: "qrc:/icons/hardware_developer_board.svg"
                text: "WorkBench"
                MouseArea {
                    anchors.fill: parent
                    onClicked: contentLoader.sourceComponent = workbenchPage;
                }
            }
        }

        Rectangle {
            id: sideBarSpacer
            anchors.top: parent.top
            width: textMargins / 2
            anchors.bottom: parent.bottom
            anchors.left: sideBar.right
            color: sideBarColor
        }

        Rectangle {
            id: contentContainer
            anchors.right: parent.right
            anchors.left: sideBarSpacer.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: contentColor

            Loader {
                id: contentLoader
                anchors.fill: parent
                sourceComponent: scanConfigurationPage
                focus: true
            }
        }
    }
    FileSaveDialog{
        id: startCollectionDialog
        visible: false
        title: "Please choose the collection filename"
        nameFilters: [ "rf phreaker files (*.rfp)", "All files (*)" ]
//        modality: Qt.WindowModal
//        folder: shortcuts.documents
//        selectedNameFilter: "rf phreaker files (*.rfp)"
//        sidebarVisible: true
        onAccepted: {
            Api.collectionFilename = fileUrl;
            console.log("collection filename is" + fileUrl);
            dsmOperation.startRecording();
        }
        onRejected: { console.log("Cancelled save collection filename.") }
    }
}

