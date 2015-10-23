import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

ScrollView {
    id: scrollView
    anchors.fill: parent
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Flickable {
        anchors.fill: parent
        contentWidth: viewport.width

        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.margins: textMargins / 2
            columnSpacing: textMargins / 2
            rowSpacing: textMargins / 2
            columns: Math.max(1, Math.floor(scrollView.width / Math.max(scannerGroup.implicitWidth, gpsGroup.implicitWidth, licenses.implicitWidth)))

            GroupBox {
                id: scannerGroup
                title: "Scanner"
                flat: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                GridLayout {
                    id: scannerDetailsLayout
                    columns: 2
                    columnSpacing: textMargins / 2
                    rowSpacing: textMargins / 2
                    anchors.fill: parent

                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Serial"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.connectedDevice.serial
                    }
                    Label {
                        id: freqCorrectionDate
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Frequency Correction Date"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.connectedDevice.freqCorrectionDateStr;
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "RF Calibration Date"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.connectedDevice.rfCalibrationDateStr
                    }
                    RowLayout {
                        id: buttonLayout
                        Layout.columnSpan: scannerDetailsLayout.columns
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignRight

                        Button {
                            text: "Disconnect"
                            enabled: Api.connectionStatus === ApiTypes.CONNECTED
                            onClicked: {
                                Api.disconnectDevice();
                            }
                        }
                        Button {
                            text: "Connect"
                            enabled: Api.connectionStatus === ApiTypes.DISCONNECTED
                            onClicked: {
                                dsmOperation.connectScanner();
                            }
                        }
//                        Button {
//                            enabled: Api.deviceStatus === ApiTypes.IDLE
//                            text: "Update License"
//                        }
                    }
                }
            }

            GroupBox {
                id: gpsGroup
                title: "GPS"
                flat: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop | Qt.AlignLeft

                GridLayout {
                    id: gpsDetailsLayout
                    columns: 2
                    columnSpacing: textMargins / 2
                    rowSpacing: textMargins / 2
                    anchors.fill: parent

                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Universal Time Coordinate"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.utcDateTime
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "GPS Locked"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.gpsLock ? "TRUE" : "FALSE"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Latitude"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.gpsLock === true ? Number(Api.gps.latitude).toPrecision(6) : "Unknown"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Longitude"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.gpsLock === true ? Number(Api.gps.longitude).toPrecision(6) : "Unknown"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Satellites Tracking"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.trackingSatellites
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: "Satellites Visible"
                    }
                    Label {
                        font.family: Flat.FlatStyle.fontFamily
                        font.pixelSize: scannerDetailsPixelSize
                        renderType: Text.QtRendering
                        text: Api.gps.visibleSatellites
                    }
                }
            }

            GroupBox {
                id: licenses
                title: "Licenses"
                flat: false
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignTop
                Layout.columnSpan: mainGrid.columns

                GridLayout {
                    id: licenseGrid
                    anchors.fill: parent
                    columnSpacing: textMargins / 2
                    rowSpacing: textMargins / 2

                    TableView {
                        id: guilicenses
                        frameVisible: false
                        backgroundVisible: true
                        alternatingRowColors: false
                        headerVisible: false
                        Layout.fillHeight: true
                        implicitWidth: 240
                        Layout.column: 0
                        selectionMode: SelectionMode.NoSelection

                        TableViewColumn {
                            role: "license"
                            title: "License"
                            width: 120//fontMetrics.advanceWidth("Basic Operation")
                        }
                        TableViewColumn {
                            role: "detail"
                            title: "??"
                            width: 120//fontMetrics.advanceWidth("Enabled")
                        }

                        model: ListModel {
                            ListElement {
                                license: "Basic Operation"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "Layer 3 Decoding"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "Data Analysis"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "Mapping"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "Workbench"
                                detail: "Enabled"
                            }
                        }
                    }
                    TableView {
                        id: freqLicenses
                        frameVisible: false
                        backgroundVisible: true
                        alternatingRowColors: false
                        headerVisible: false
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.column: 1
                        selectionMode: SelectionMode.NoSelection

                        TableViewColumn {
                            role: "license"
                            title: "License"
                            width: 140//fontMetrics.advanceWidth("WCMDA BAND 15")
                        }
                        TableViewColumn {
                            role: "freqRange"
                            title: "freqRange"
                        }
                        TableViewColumn {
                            role: "detail"
                            title: "??"
                            width: 120//fontMetrics.advanceWidth("Enabled")
                        }

                        model: ListModel {
                            ListElement {
                                license: "GSM BAND E750"
                                freqRange: "726 - 789 mhz"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "GSM BAND 850"
                                freqRange: "810 - 896 mhz"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "GSM 1800 DCS"
                                freqRange: "1810 - 1885 mhz"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "GSM 1900 PCS"
                                freqRange: "1930 - 1990 mhz"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "WCMDA BAND 1"
                                freqRange: "869 - 893 mhz"
                                detail: "Disabled"
                            }
                            ListElement {
                                license: "WCMDA BAND 5"
                                freqRange: "2110 - 2170 mhz"
                                detail: "Enabled"
                            }
                            ListElement {
                                license: "WCMDA BAND 15"
                                freqRange: "2450 - 2600 mhz"
                                detail: "Disabled"
                            }
                        }
                    }
                    Button {
                        Layout.column: 1
                        Layout.row: 1
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        text: "Update License"
                        enabled: Api.deviceStatus === ApiTypes.IDLE
                        onClicked: {
                            fileDialog.open();
                        }
                    }
                }

            }
        }
    }
    property FileDialog fileDialog: FileDialog {
        id: fileDialog
        title: "Choose license file"
        folder: shortcuts.home
        nameFilters: [ "License files (*.lic)", "All files (*)" ]
        selectMultiple: false
        sidebarVisible: true
        onAccepted: {
        }
        onRejected: {
        }
    }
}
