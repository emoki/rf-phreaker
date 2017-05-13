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
            var name = "item " + item.meas.measurementFreq;
            var areaSeries = chart.createSeries(ChartView.SeriesTypeArea, name, mainAxisX, mainAxisY);
            item.lineSeries = areaSeries.upperSeries;
            var model = Api.getSweepModel(item.meas);

            // For GSM the bandwidth is so small that only one point will pass the filter
            // so a line will not be drawn.  Thus we fall back to drawing the line separate
            // from the sweep line.
            if(model && item.meas.measurementBandwidth > .2) {
                item.sourceModel = model;
            }
//            console.debug("itemSweepLine added - freq: ", item.meas.measurementFreq, "channel: ", item.meas.cellChannel, "  cellid: ",
//                          item.meas.cellId, "  bandwidth: ", item.meas.measurementBandwidth, "  series:", item.lineSeries.name);
        }
        onItemRemoved: {
//            console.debug("itemSweepLine removed - freq: ", item.meas.measurementFreq, "channel: ", item.meas.cellChannel, "  cellid: ",
//                          item.meas.cellId, "  bandwidth: ", item.meas.measurementBandwidth, "  series:", item.lineSeries.name);
        }
    }
}
