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

//    function loadAnalysisSelection() {
//        loader.sourceComponent = analysisSelection;
//    }

    Component.onCompleted: loader.sourceComponent = scrollView.analysisSelection

    property DataWorksheet dataWorksheet : Component { DataWorksheet {} }
    property OverviewChart overviewChart : Component { OverviewChart {} }
    property BarChart barChart : Component { BarChart{} }
    Flickable {
        id: flick
        anchors.fill: parent
        contentWidth: viewport.width

        Loader {
            id: loader
            anchors.fill: parent
        }
    }
    property GridLayout analysisSelection: Component {
        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.centerIn: parent
            anchors.margins: textMargins / 2
            columnSpacing: textMargins / 2
            rowSpacing: textMargins / 2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            columns: Math.max(
                         1, Math.floor(
                             loader.width / dataAnalayisOverview.width))

            DataAnalysisLabel {
                id: dataAnalayisOverview
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "Spectrum Overview"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainGrid.enabled = false;
                        mainGrid.visible = false;
                        loader.sourceComponent = overviewChart;
                    }
                }
            }
            DataAnalysisLabel {
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "Spreadsheet"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainGrid.enabled = false;
                        mainGrid.visible = false;
                        loader.sourceComponent = dataWorksheet;
                    }
                }
            }
            DataAnalysisLabel {
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "Bar Graph"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainGrid.enabled = false;
                        mainGrid.visible = false;
                        loader.sourceComponent = barChart;
                    }
                }
            }
            DataAnalysisLabel {
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "Drill Down"
            }
            DataAnalysisLabel {
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "IQ Plot"
            }
            DataAnalysisLabel {
                source: "qrc:/icons/icons/ic_insert_chart_black_48dp.png"
                text: "Spectrum\nGraph"
            }
        }
    }
}
