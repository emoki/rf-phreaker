import QtQuick 2.5
import RfPhreaker 1.0
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Dialogs 1.2
import Material.ListItems 0.1 as ListItem


TabbedPage {
    id: page
    title: "RF Phreaker Measurements"

    actions: [
        Action {
            name: "Convert RPF file to ASCII"
            iconName: "av/note"
            onTriggered: rpfConversionDialog.open();
        },
        Action {
            id: startRecording
            visible: Api.deviceStatus !== ApiTypes.RECORDING
            enabled: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.IDLE
            name: "Record Data"
            shortcut: "Ctrl+R"
            iconName: "av/play_circle_filled"
            onTriggered: {
                rpWindow.startCollectionDialog.filename = "collection_data_" +
                        Qt.formatDateTime(new Date(), "yyyy-MMM-dd_hh-mm-ss");
                rpWindow.startCollectionDialog.open()
            }
        },
        Action {
            id: stopRecording
            visible: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.RECORDING
            name: "Stop Recording"
            shortcut: "Ctrl+S"
            iconName: "av/stop"
            onTriggered: rpWindow.stateMachine.stopScanning()
        },
        Action {
            name: "Show Log"
            shortcut: "Ctrl+L"
            iconName: "action/subject"
            onTriggered: rpWindow.showLog()
        }
    ]

    Tab {
        id: lteTab
        title: "LTE"

        RowLayout {
            id: lteGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }

            spacing: dp(16)

            ColumnLayout {
                Layout.maximumWidth: lteGrid.width * .7
                Layout.fillHeight: true
                spacing: dp(16)

                OverviewChartSweepChannel {
                    id: lteOverviewChart
                    Layout.fillWidth: true
                    Layout.preferredHeight: lteGrid.height * .3

                    sweepModelList: Api.lteModels.sweepModelList
                    channelModel: Api.lteModels.highestCellPerChannelModel

                    xMin: Api.lteModels.lowestFreq
                    xMax: Api.lteModels.highestFreq
                    yMin: -120
                    yMax: -10

                }
                MaterialMeasurementTable {
                    id: lteDataWorksheet

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    sourceModel: Api.lteModels.fullScanModel

                    onFilteredModelUpdated: lteBarChart.update();
                }
            }
            BarChart {
                id: lteBarChart
                Layout.fillHeight: true
                Layout.fillWidth: true

                sourceModel: lteDataWorksheet.filteredModel

                slMin: -120
                slMax: -10
            }
        }
    }

    Tab {
        id: wcdmaTab
        title: "WCDMA"

        RowLayout {
            id: wcdmaGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }

            spacing: dp(16)

            ColumnLayout {
                Layout.maximumWidth: wcdmaGrid.width * .7
                Layout.fillHeight: true
                spacing: dp(16)

                OverviewChartSweepChannel {
                    id: wcdmaOverviewChart
                    Layout.fillWidth: true
                    Layout.preferredHeight: wcdmaGrid.height * .3

                    sweepModelList: Api.wcdmaModels.sweepModelList
                    channelModel: Api.wcdmaModels.highestCellPerChannelModel

                    xMin: Api.wcdmaModels.lowestFreq
                    xMax: Api.wcdmaModels.highestFreq
                    yMin: -120
                    yMax: -10

                }
                MaterialMeasurementTable {
                    id: wcdmaDataWorksheet

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    sourceModel: Api.wcdmaModels.fullScanModel

                    onFilteredModelUpdated: wcdmaBarChart.update();
                }
            }
            BarChart {
                id: wcdmaBarChart
                Layout.fillHeight: true
                Layout.fillWidth: true

                sourceModel: wcdmaDataWorksheet.filteredModel

                slMin: -120
                slMax: -10
            }
        }
    }

    Tab {
        id: gsmTab
        title: "GSM"

        RowLayout {
            id: gsmGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }

            spacing: dp(16)

            ColumnLayout {
                Layout.maximumWidth: gsmGrid.width * .7
                Layout.fillHeight: true
                spacing: dp(16)

                OverviewChartSweepChannel {
                    id: gsmOverviewChart
                    Layout.fillWidth: true
                    Layout.preferredHeight: gsmGrid.height * .3

                    sweepModelList: Api.gsmModels.sweepModelList
                    channelModel: Api.gsmModels.highestCellPerChannelModel

                    xMin: Api.gsmModels.lowestFreq
                    xMax: Api.gsmModels.highestFreq
                    yMin: -120
                    yMax: -10

                }
                MaterialMeasurementTable {
                    id: gsmDataWorksheet

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    sourceModel: Api.gsmModels.fullScanModel

                    onFilteredModelUpdated: gsmBarChart.update();
                }
            }
            BarChart {
                id: gsmBarChart
                Layout.fillHeight: true
                Layout.fillWidth: true

                sourceModel: gsmDataWorksheet.filteredModel

                slMin: -120
                slMax: -10
            }
        }
    }

    FileDialog {
        id: rpfConversionDialog
        visible: false
        title: "Choose RPF Files For Conversion"
        nameFilters: [ "rf phreaker files (*.rpf)" ]
        modality: Qt.WindowModal
        folder: shortcuts.documents
        selectedNameFilter: "rf phreaker files (*.rpf)"
        sidebarVisible: true
        selectExisting: true
        selectMultiple: true
        onAccepted: {
            console.log("RPF files to convert: " + fileUrls);
            for(var i = 0; i < fileUrls.length; ++i)
                Api.convertRfp(fileUrls[i]);
        }
        onRejected: { console.log("Canceled RPF conversion dialog.") }
    }
}
