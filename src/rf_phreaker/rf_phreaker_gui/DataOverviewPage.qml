import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtCharts 2.1
import RfPhreaker 1.0

ScrollView {
    property alias sweepModel: overviewChart.sweepModelList
    property alias sweepChannelModel: overviewChart.channelModel
    property alias fullScanModel: dataWorksheet.sourceModel
    property alias overviewXMin: overviewChart.xMin
    property alias overviewXMax: overviewChart.xMax
    property alias overviewYMin: overviewChart.yMin
    property alias overviewYMax: overviewChart.yMax
    property alias barSLMin: barChart.slMin
    property alias barSLMax: barChart.slMax

    id: scannerScrollView
    anchors.fill: parent
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Flickable {
        anchors.fill: parent

        GridLayout {
            id: grid
            anchors.fill: parent
            columns: 5

            OverviewChart {
                id: overviewChart
                Layout.column: 1
                Layout.columnSpan: 2
                Layout.row: 1
                Layout.preferredWidth: grid.width * .7
                Layout.preferredHeight: grid.height * .7
                //theme: ChartView.ChartThemeDark
            }
            BarChart {
                id: barChart
                Layout.column: 3
                Layout.columnSpan: 3
                Layout.row: 1
                Layout.preferredWidth: grid.width - overviewChart.width
                Layout.preferredHeight: grid.height * .7
                sourceModel: dataWorksheet.filteredModel
                //theme: ChartView.ChartThemeDark
            }
            Rectangle {
                Layout.column: 1
                Layout.row: 2
                Layout.preferredWidth: 5
            }
            DataWorksheet {
                id: dataWorksheet
                Layout.column: 2
                Layout.columnSpan: 1
                Layout.row: 2
                Layout.preferredWidth: grid.width * .7
                Layout.preferredHeight: grid.height * .5
                sourceModel: fullScanModel
                onFilteredModelUpdated: barChart.update();
            }
            Rectangle {
                Layout.column: 3
                Layout.row: 2
                Layout.preferredWidth: 5
            }
        }
    }
}
