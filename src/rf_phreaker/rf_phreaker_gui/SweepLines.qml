import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    property ChartView chart
    property ValueAxis mainAxisX
    property ValueAxis mainAxisY
    property alias sourceModel: repeater.model
    Repeater {
        id: repeater
        SweepLine {
            sourceModel: modelData
        }
        onItemAdded: {
            var line = chart.createSeries(ChartView.SeriesTypeLine, "sweep" + index, mainAxisX, mainAxisY);
            //line.color = Api.getColorTheme()
            line.useOpenGL = true;
            item.lineSeries = line;
        }
    }
}

