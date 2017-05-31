import QtQuick 2.6
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtCharts 2.1
import RfPhreaker 1.0

OverviewChart {
    id: overviewChartSweepChannel
    property alias sweepModelList: sweepLines.sourceModel
    property alias channelModel: channelSweepLines.sourceModel

    SweepLines {
        id: sweepLines
        chart: overviewChartSweepChannel
        mainAxisX: overviewAxisX
        mainAxisY: overviewAxisY
        //sourceModel: Api.sweepModelList
    }
    ChannelSweepLines {
        id: channelSweepLines
        chart: overviewChartSweepChannel
        mainAxisX: overviewAxisX
        mainAxisY: overviewAxisY
        //sourceModel: Api.highestCellPerChannelModel
    }
}
