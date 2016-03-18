import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtCharts 2.1
import RfPhreaker 1.0

ChartView {
    id: barChart
    property var yMin: -130
    property var yMax: 0

    title: "Bar Chart"
    antialiasing: true
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    //legend.visible: false
    focus: true

    ValueAxis {
        id: barAxisX
        min: -120
        max: -10
        gridVisible: true
        minorGridVisible: true
        tickCount: 5
    }

    ChannelBarLines {
        id: channelBarLines
        chart: barChart
        mainAxisX: barAxisX
        sourceModel: Api.wcdmaFullScanModel
    }
}
