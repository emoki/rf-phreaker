import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtCharts 2.1
import RfPhreaker 1.0

ChartView {
    id: barChart
    property var sourceModel
    property var slMin: -120
    property var slMax: -20

    //title: "Bar Chart"
    antialiasing: true
    animationOptions: ChartView.NoAnimation
    //theme: ChartView.ChartThemeDark
    legend.visible: false
    focus: true

    margins {
        right: 0
        left: 0
        top: 0
        bottom: 0
    }

    ValueAxis {
        id: barAxisX
        min: slMin
        max: slMax
        gridVisible: true
        minorGridVisible: true
        tickCount: 5
        //labelsFont: graphingLabel.font
    }

    LineSeries{
        id: dummy
        axisX: barAxisX
        axisY: ValueAxis { visible: false }
    }

    ChannelBarLines {
        id: channelBarLines
        chart: barChart
        mainAxisX: barAxisX
        sourceModel: barChart.sourceModel
    }

    function update() {
        channelBarLines.refresh();
    }
}
