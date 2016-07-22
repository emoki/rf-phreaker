import QtQuick 2.5
import RfPhreaker 1.0
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import Material.ListItems 0.1 as ListItem


TabbedPage {
    id: page
    title: "RF Phreaker Measurements"

    actions: [
        Action {
            iconName: "navigation/more_vert"
            name: "More Options"
            hoverAnimation: true
        }
    ]

    Tab {
        id: wcdmaTab
        title: "WCDMA"

        GridLayout {
            id: wcdmaGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16*2)
            }

            columnSpacing: dp(32)
            rowSpacing: dp(32)

            columns: 10
            rows: 2

            OverviewChart {
                id: wcdmaOverviewChart
                Layout.column: 0
                Layout.columnSpan: 7
                Layout.row: 0
                Layout.preferredWidth: wcdmaGrid.width * .7
                Layout.preferredHeight: wcdmaGrid.height * .3

                sweepModelList: Api.wcdmaModels.sweepModelList
                channelModel: Api.wcdmaModels.highestCellPerChannelModel

                xMin: Api.wcdmaModels.lowestFreq
                xMax: Api.wcdmaModels.highestFreq
                yMin: -120
                yMax: -10

            }

            BarChart {
                id: wcdmaBarChart
                Layout.column: 7
                Layout.columnSpan: 3
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.preferredWidth: wcdmaGrid.width - wcdmaOverviewChart.width
                Layout.preferredHeight: wcdmaGrid.height

                sourceModel: wcdmaDataWorksheet.filteredModel

                slMin: -120
                slMax: -10
            }
            MaterialMeasurementTable {
                id: wcdmaDataWorksheet

                Layout.column: 0
                Layout.columnSpan: 7
                Layout.row: 1
                Layout.preferredWidth: wcdmaGrid.width * .7
                Layout.preferredHeight: wcdmaGrid.height * .7

                sourceModel: Api.wcdmaModels.fullScanModel

                onFilteredModelUpdated: wcdmaBarChart.update();
            }
        }
    }

    Tab {
        title: "LTE"

        GridLayout {
            id: lteGrid
            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16*2)
            }

            columnSpacing: dp(32)
            rowSpacing: dp(32)

            columns: 10
            rows: 2

            OverviewChart {
                id: lteOverviewChart
                Layout.column: 0
                Layout.columnSpan: 7
                Layout.row: 0
                Layout.preferredWidth: lteGrid.width * .7
                Layout.preferredHeight: lteGrid.height * .3

                sweepModelList: Api.lteModels.sweepModelList
                channelModel: Api.lteModels.highestCellPerChannelModel

                xMin: Api.lteModels.lowestFreq
                xMax: Api.lteModels.highestFreq
                yMin: -120
                yMax: -10

            }

            BarChart {
                id: lteBarChart
                Layout.column: 7
                Layout.columnSpan: 3
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.preferredWidth: lteGrid.width - lteOverviewChart.width
                Layout.preferredHeight: lteGrid.height

                sourceModel: lteDataWorksheet.filteredModel

                slMin: -120
                slMax: -10
            }
            MaterialMeasurementTable {
                id: lteDataWorksheet

                Layout.column: 0
                Layout.columnSpan: 7
                Layout.row: 1
                Layout.preferredWidth: lteGrid.width * .7
                Layout.preferredHeight: lteGrid.height * .7

                sourceModel: Api.lteModels.fullScanModel

                onFilteredModelUpdated: lteBarChart.update();
            }
        }
    }
}
