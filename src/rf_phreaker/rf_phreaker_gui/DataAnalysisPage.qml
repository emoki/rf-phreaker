import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

//ScrollView {
//    id: scrollView
//    anchors.fill: parent
//    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    TabView {
        anchors.fill: parent
        Tab {
            title: "WCDMA"
            anchors.fill: parent
            DataOverviewPage {
                anchors.fill: parent
                sweepModel: Api.wcdmaModels.sweepModelList
                sweepChannelModel: Api.wcdmaModels.highestCellPerChannelModel
                fullScanModel: Api.wcdmaModels.fullScanModel
                overviewXMin: Api.wcdmaModels.lowestFreq
                overviewXMax: Api.wcdmaModels.highestFreq
                overviewYMin: -120
                overviewYMax: -10
                barSLMin: -120
                barSLMax: -10
            }
        }
        Tab {
            title: "LTE"
            anchors.fill: parent
            DataOverviewPage {
                anchors.fill: parent
                sweepModel: Api.lteModels.sweepModelList
                sweepChannelModel: Api.lteModels.highestCellPerChannelModel
                fullScanModel: Api.lteModels.fullScanModel
                overviewXMin: Api.lteModels.lowestFreq
                overviewXMax: Api.lteModels.highestFreq
                overviewYMin: -140
                overviewYMax: -10
                barSLMin: -140
                barSLMax: -10
            }
        }
    }

//    function loadAnalysisSelection() {
//        loader.sourceComponent = analysisSelection;
//    }

//    Component.onCompleted: loader.sourceComponent = scrollView.analysisSelection

//    property DataWorksheet dataWorksheet : Component { DataWorksheet {} }
//    property OverviewChart overviewChart : Component { OverviewChart {} }
//    property BarChart barChart : Component { BarChart{} }
//    property DataOverviewPage umtsPage: Component {
//        DataOverviewPage {
//            sweepModel: Api.wcdmaModels.sweepModelList
//            sweepChannelModel: Api.wcdmaModels.highestCellPerChannelModel
//            fullScanModel: Api.wcdmaModels.fullScanModel
//            overviewXMin: Api.wcdmaModels.lowestFreq
//            overviewXMax: Api.wcdmaModels.highestFreq
//            overviewYMax: -10
//            overviewYMin: -140
//            barSLMin: -140
//            barSLMax: -10
//        }
//    }
//    Flickable {
//        id: flick
//        anchors.fill: parent
//        contentWidth: viewport.width

//        Loader {
//            id: loader
//            anchors.fill: parent
//        }
//    }
//    property GridLayout analysisSelection: Component {
//        GridLayout {
//            id: mainGrid
//            anchors.fill: parent
//            anchors.centerIn: parent
//            anchors.margins: textMargins / 2
//            columnSpacing: textMargins / 2
//            rowSpacing: textMargins / 2
//            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
//            columns: Math.max(
//                         1, Math.floor(
//                             loader.width / dataAnalayisOverview.width))

//            DataAnalysisLabel {
//                id: dataAnalayisOverview
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "Spectrum Overview"
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        mainGrid.enabled = false;
//                        mainGrid.visible = false;
//                        loader.sourceComponent = overviewChart;
//                    }
//                }
//            }
//            DataAnalysisLabel {
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "Spreadsheet"
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        mainGrid.enabled = false;
//                        mainGrid.visible = false;
//                        loader.sourceComponent = dataWorksheet;
//                    }
//                }
//            }
//            DataAnalysisLabel {
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "Bar Graph"
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        mainGrid.enabled = false;
//                        mainGrid.visible = false;
//                        loader.sourceComponent = barChart;
//                    }
//                }
//            }
//            DataAnalysisLabel {
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "UMTS"
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: {
//                        mainGrid.enabled = false;
//                        mainGrid.visible = false;
//                        loader.sourceComponent = umtsPage;
//                    }
//                }
//            }
//            DataAnalysisLabel {
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "IQ Plot"
//            }
//            DataAnalysisLabel {
//                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
//                text: "Spectrum\nGraph"
//            }
//        }
//    }
//}
