import QtQuick 2.7
import RfPhreaker 1.0
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Dialogs 1.2
import QtDataVisualization 1.2
import QtCharts 2.2
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

    Tab {
        id: cwTab
        title: "CW"

        RowLayout {
            id: cwGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }

            spacing: dp(16)

            ColumnLayout {
                Layout.maximumWidth: cwGrid.width * .4
                Layout.fillHeight: true
                spacing: dp(16)

                MaterialMeasurementTable {
                    id: cwDataWorksheet

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    sourceModel: Api.cwModel

                    onFilteredModelUpdated: cwBarChart.update();

                    onTableViewCompleted: {
                        cwDataWorksheet.removeAllColumns();
                        cwDataWorksheet.insertColumn("dwellTimeRole", false, 0);
                        cwDataWorksheet.insertColumn("binSizeRole", false, 0);
                        cwDataWorksheet.insertColumn("cellSignalLevel", false, 0);
                        cwDataWorksheet.insertColumn("identifierRole", false, 0);
                    }
                }
            }
            BarChart {
                id: cwBarChart
                Layout.fillHeight: true
                Layout.fillWidth: true

                sourceModel: cwDataWorksheet.filteredModel

                displaySecondArea: false

                slMin: -160
                slMax: -10
            }
        }
    }

    Tab {
        id: spectrumTab
        title: "Spectrum"

        ColumnLayout {
            id: spectrumGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }
            spacing: dp(16)

            function update() {
                for(var i = 0; i < spectrumOverviewChart.count; ++i) {
                    Api.spectrumManager.updateLineSeries(spectrumOverviewChart.series(i), i);
                }
                for(var j = 0; j < spectrumWaterfall.seriesList.length; ++j) {
                    Api.spectrumManager.updateSurfaceSeries(spectrumWaterfall.seriesList[j], j);
                }
            }

            function create() {
                // Account for dummy series
                for(var i = spectrumOverviewChart.count; i < Api.spectrumManager.numItems; ++i) {
                    var line = spectrumOverviewChart.createSeries(ChartView.SeriesTypeLine, i,
                                                                  spectrumOverviewChart.overviewAxisX, spectrumOverviewChart.overviewAxisY);
                    line.useOpenGl = true;
                }
                for(var j = spectrumWaterfall.seriesList.length; j < Api.spectrumManager.numItems; ++j) {
                    spectrumWaterfall.addSeries(Api.spectrumManager.createSurfaceSeries(j));
                }

            }

            Timer {
                id: specRefresh
                interval: 300
                running: true
                repeat: true
                onTriggered: spectrumGrid.update()
            }

            Connections {
                target: Api.spectrumManager
                onNumItemsChanged: spectrumGrid.create()
                onFinishedReset: {
                    spectrumOverviewChart.removeAllSeries();
                    while(spectrumWaterfall.seriesList.length)
                        spectrumWaterfall.removeSeries(spectrumWaterfall.seriesList[0]);
                }
            }

            Component.onCompleted: {
                spectrumGrid.create();
                spectrumGrid.update();
            }

            OverviewChart {
                id: spectrumOverviewChart

                Layout.fillWidth: true
                Layout.preferredHeight: spectrumGrid.height * .5

                xMin: (Api.spectrumManager.freqLimits.low < 300 || Api.spectrumManager.freqLimits.low > 2600) ? 300 : Api.spectrumManager.freqLimits.low
                xMax: (Api.spectrumManager.freqLimits.high > 2600 || Api.spectrumManager.freqLimits.high < 300) ? 2600 : Api.spectrumManager.freqLimits.high
                yMin: -160
                yMax: -10
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: Api.spectrumManager.isDisabled
                Text {
                    id: noWaterfallLabel
                    anchors.centerIn: parent
                    color: Theme.light.subTextColor
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font.pixelSize: 100
                    font.family: "Roboto"
                    text: "Waterfall plot disabled"
                    opacity: .25
                }
            }

            Item {
                id: surface
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: !Api.spectrumManager.isDisabled

                ColorGradient {
                    id: surfaceGradient
                    ColorGradientStop { position: 0.0; color: "blue" }
                    ColorGradientStop { position: 0.25; color: "lightblue" }
                    ColorGradientStop { position: 0.55; color: "green" }
                    ColorGradientStop { position: 0.75; color: "yellow" }
                    ColorGradientStop { position: 1.0; color: "red" }
                }

                Surface3D {
                    id: spectrumWaterfall
                    width: spectrumOverviewChart.plotArea.width
                    height: surface.height
                    x: spectrumOverviewChart.plotArea.x

                    shadowQuality: AbstractGraph3D.ShadowQualityNone
                    selectionMode: AbstractGraph3D.SelectionSlice | AbstractGraph3D.SelectionItemAndRow
                    scene.activeCamera.cameraPreset: Camera3D.CameraPresetDirectlyAbove
                    orthoProjection: true


                    // Using the width / height ratio allows us to precisely match the overviewchart.
                    horizontalAspectRatio: spectrumWaterfall.width / spectrumWaterfall.height
                    scene.activeCamera.zoomLevel: spectrumWaterfall.width / spectrumWaterfall.height * 100

                    // Margin keeps the border away so we don't see the graph lines.
                    margin: 100
                    axisY.min: -160
                    axisY.max: -10
                    axisX.min: spectrumOverviewChart.overviewAxisX.min
                    axisX.max: spectrumOverviewChart.overviewAxisX.max
                    axisZ.min: 0
                    axisZ.max: Api.spectrumManager.capacity
                    axisY.title: ""
                    axisX.title: ""
                    axisZ.title: ""
                    axisX.labelAutoRotation: 0
                    axisY.labelAutoRotation: 0
                    axisZ.labelAutoRotation: 0
                    axisX.labelFormat: ""
                    axisY.labelFormat: ""
                    axisZ.labelFormat: ""
                    axisX.segmentCount: 1
                    axisX.subSegmentCount: 1
                    axisZ.segmentCount: 1
                    axisZ.subSegmentCount: 1

                    theme: Theme3D {
                        type: Theme3D.ThemeDigia
                        colorStyle: Theme3D.ColorStyleRangeGradient
                        baseGradients: [surfaceGradient]
                    }

//                    Surface3DSeries {
//                        id: surfaceSeries
//                        drawMode: Surface3DSeries.DrawSurface
//                        meshSmooth: false
//                        flatShadingEnabled: false
//                    }
                }
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
