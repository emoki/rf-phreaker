import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelSweepLines
    property ChartView chart
    property ValueAxis mainAxisX
    property ValueAxis mainAxisY
    property alias sourceModel: repeater.model

    Repeater {
        id: repeater

        ChannelSweepLine {
            id: channel
        }
        onItemAdded: {
            item.meas = sourceModel.data(sourceModel.index(index, 0), MeasurementModel.BasicMeasRole);
            var areaSeries = chart.createSeries(ChartView.SeriesTypeArea, "item " + item.meas.cellitem, mainAxisX, mainAxisY);
            item.lineSeries = areaSeries.upperSeries;
            var model = Api.getSweepModel(item.meas);
            if(model) {
                item.sourceModel = model;
            }
        }
    }
}
