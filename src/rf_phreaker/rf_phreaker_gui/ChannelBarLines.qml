import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelBarLines
    property ChartView chart
    property ValueAxis mainAxisX
   // property alias sourceModel: filter.sourceModel
   // property alias sourceModel: repeater.model
    property alias sourceModel: repeater.model
    property alias catAxis: mainAxisY
    CategoryAxis {
        id: mainAxisY
        min: 0
        //max: 10
        max: repeater.count + 1 > 9 ? repeater.count : 10
        gridVisible: false
        reverse: Qt.Vertical
        lineVisible: false
        //labelsFont: graphingLabel.font
    }

    Repeater {
        id: repeater
        property int barSeriesIndex: 0;

        ChannelBarLine {
            id: channel
        }

        onItemAdded: {
            //console.debug("item added ------", barSeriesIndex);
            item.chart = chart;
            item.mainAxisX = mainAxisX;
            item.mainAxisY = mainAxisY;
            createAttachMeasBar(barSeriesIndex, item)
            barSeriesIndex += 1;
            if(barSeriesIndex == repeater.count)
                refresh();
        }
        onItemRemoved: {
            barSeriesIndex -= 1;
            //console.debug("item removed -----", barSeriesIndex);
            removeMeasBar(barSeriesIndex);
            if(barSeriesIndex == repeater.count)
                refresh();
        }
    }

    function createAttachMeasBar(index, item) {
        var upperId = index + "_" + "Upper";
        var lowerId = index + "_" + "Lower"

        item.areaSeriesSL = chart.series(upperId);
        if(item.areaSeriesSL === null) {
            item.areaSeriesSL = chart.createSeries(ChartView.SeriesTypeArea, upperId, mainAxisX, mainAxisY, true);
        }

        item.areaSeriesInter = chart.series(lowerId);
        if(item.areaSeriesInter === null) {
            item.areaSeriesInter = chart.createSeries(ChartView.SeriesTypeArea, lowerId, mainAxisX, mainAxisY, true);
            item.areaSeriesInter.color = "grey";
        }
    }

    function removeMeasBar(index) {
        var upperId = index + "_" + "Upper";
        var lowerId = index + "_" + "Lower"
        if(chart.series(upperId) === null) {
            console.debug("Unable to find bar series.", upperId, " ", lowerId);
        }
        chart.removeSeries(chart.series(upperId));
        chart.removeSeries(chart.series(lowerId));
    }

    function refresh() {
        if(repeater.count === 0)
            return;
        mainAxisY.max = repeater.count + 1 > 9 ? repeater.count/* + 1*/ : 10;
        var borderSpacing = ((mainAxisY.max - mainAxisY.min) / repeater.count) / 6;
        var barArea = (mainAxisY.max - mainAxisY.min - 2 * borderSpacing) / repeater.count
        var barSpacing = barArea / 5;
        var barWidth = barArea - barSpacing * 2
        mainAxisY.startValue = barSpacing;

        for(var i = 0; i < repeater.count; ++i) {
            var meas = repeater.model.data(repeater.model.index(i, 0), MeasurementModel.BasicMeasRole);
            var channel = repeater.itemAt(i);

            createAttachMeasBar(i, channel)
            channel.meas = meas;
            channel.bottomY = (borderSpacing + barArea * i + barSpacing);
            channel.topY = (channel.bottomY + barWidth);
//            console.debug("channel: ", channel.meas.cellChannel, "  cellid: ", channel.meas.cellId, "  bottomY: ",
//                          channel.bottomY, "  topY: ", channel.topY, "  loc: ", channel.topY + barSpacing / 2, "  series:", channel.areaSeriesSL.name);
            channel.update();
        }
    }
}
