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
    property string upperArea: "_UpperArea"
    property string upperLineA: "_UpperA"
    property string upperLineB: "_UpperB"
    property string lowerArea: "_LowerArea"
    property string lowerLineA: "_LowerA"
    property string lowerLineB: "_LowerB"
    property bool displaySecondArea: true

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

        var upperAreaId = index + upperArea
        var upperIdA = index + upperLineA
        var upperIdB = index + upperLineB
        var lowerAreaId = index + lowerArea;
        var lowerIdA = index + lowerLineA
        var lowerIdB = index + lowerLineB

        item.areaSeriesSL = chart.series(upperAreaId);
        if(item.areaSeriesSL === null) {
            item.areaSeriesSL = chart.createSeries(ChartView.SeriesTypeArea, upperAreaId, mainAxisX, mainAxisY);
            item.areaSeriesSL.lowerSeries = chart.createSeries(ChartView.SeriesTypeLine, upperIdB, mainAxisX, mainAxisY);
            item.areaSeriesSL.upperSeries.style = Qt.NoPen
            item.areaSeriesSL.lowerSeries.style = Qt.NoPen
        }

        if(displaySecondArea) {
            item.areaSeriesInter = chart.series(lowerAreaId);
            if(item.areaSeriesInter === null) {
                item.areaSeriesInter = chart.createSeries(ChartView.SeriesTypeArea, lowerAreaId, mainAxisX, mainAxisY);
                item.areaSeriesInter.lowerSeries = chart.createSeries(ChartView.SeriesTypeLine, lowerIdB, mainAxisX, mainAxisY);
                item.areaSeriesInter.color = "grey";
                item.areaSeriesInter.upperSeries.style = Qt.NoPen
                item.areaSeriesInter.lowerSeries.style = Qt.NoPen
            }
        }
    }

    function removeMeasBar(index) {
        var upperAreaId = index + upperArea
        var upperIdA = index + upperLineA
        var upperIdB = index + upperLineB
        var lowerAreaId = index + lowerArea;
        var lowerIdA = index + lowerLineA
        var lowerIdB = index + lowerLineB
//        if(chart.series(upperAreaId) === null
//                || chart.series(upperIdB) === null
//                || chart.series(lowerAreaId) === null
//                || chart.series(lowerIdB) === null ) {
//            console.debug("Unable to find bar series.");
//            console.debug(chart.series(upperAreaId), chart.series(upperIdA), chart.series(upperIdB),
//                          chart.series(lowerAreaId), chart.series(lowerIdA), chart.series(lowerIdB))
//        }
        chart.removeSeries(chart.series(upperAreaId))
        chart.removeSeries(chart.series(upperIdB));
        if(displaySecondArea) {
            chart.removeSeries(chart.series(lowerAreaId))
            chart.removeSeries(chart.series(lowerIdB));
        }
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
            var measLabel = repeater.model.data(repeater.model.index(i,0), MeasurementModel.GraphLabelRole);
            var channel = repeater.itemAt(i);

            createAttachMeasBar(i, channel)
            channel.meas = meas;
            channel.title = measLabel;
            channel.bottomY = (borderSpacing + barArea * i + barSpacing);
            channel.topY = (channel.bottomY + barWidth);
//            console.debug("channel: ", channel.meas.cellChannel, "  cellid: ", channel.meas.cellId, "  bottomY: ",
//                          channel.bottomY, "  topY: ", channel.topY, "  loc: ", channel.topY + barSpacing / 2, "  series:", channel.areaSeriesSL.name);
            channel.update();
        }
    }
}
