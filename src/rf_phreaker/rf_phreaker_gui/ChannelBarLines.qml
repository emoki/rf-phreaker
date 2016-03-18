import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelBarLines
    property ChartView chart
    property ValueAxis mainAxisX
    property alias sourceModel: filter.sourceModel
    property real borderSpacing
    property real barArea
    property real barSpacing
    property real barWidth
    property alias catAxis: mainAxisY
    CategoryAxis {
        id: mainAxisY
        min: 0
        max: 10
        gridVisible: false
        reverse: Qt.Vertical
        lineVisible: false
    }

    FilterProxyMeasurementModel {
        id: filter
        filterRole: FilterProxyMeasurementModel.NoFilterRole
        dynamicSortFilter: false
        onRowsInserted: {
            console.debug("rows inserted")
//            sort(MeasurementModel.CellIdColumn);
//            sort(MeasurementModel.CellChannelColumn);
//            // Repopulate repeater
//            repeater.model = null
//            repeater.model = filter;
        }
    }

    Repeater {
        id: repeater
        model: filter
        ChannelBarLine {
            id: channel
        }
        onItemAdded: {
            console.debug("item added");
            item.meas = filter.data(filter.index(index, 0), MeasurementModel.BasicMeasRole);
            var upperId = item.meas.cellChannel + "_" + item.meas.cellId + "Upper";
            var lowerId = item.meas.cellChannel + "_" + item.meas.cellId + "Lower"
            item.chart = chart;
            item.mainAxisX = mainAxisX;

            item.areaSeriesSL = chart.series(upperId);
            if(item.areaSeriesSL === null) {
                item.areaSeriesSL = chart.createSeries(ChartView.SeriesTypeArea, upperId, mainAxisX, mainAxisY, true);
            }

            item.areaSeriesInter = chart.series(lowerId);
            if(item.areaSeriesInter === null) {
                item.areaSeriesInter = chart.createSeries(ChartView.SeriesTypeArea, lowerId, mainAxisX, mainAxisY, true);
            }
//            //item.areaSeries.color = Api.getColorTheme(item.meas);
            if(index == repeater.count - 1)
                refresh();
        }
    }
    function refresh(index) {
        mainAxisY.max = repeater.count + 1 > 9 ? repeater.count + 1 : 10;
        borderSpacing = ((mainAxisY.max - mainAxisY.min) / repeater.count) / 6;
        barArea = (mainAxisY.max - mainAxisY.min - 2 * borderSpacing) / repeater.count
        barSpacing = barArea / 5;
        barWidth = barArea - barSpacing * 2
        mainAxisY.startValue = barSpacing;
        var labels = mainAxisY.categoriesLabels;
        var labelCount = labels.length;
        for(var j = 0; j < labelCount; ++j) {
            mainAxisY.remove(labels[0]);
        }
        console.debug(catAxis.count);
        for(var i = 0; i < repeater.count; ++i) {
            var channel = repeater.itemAt(i);
            channel.bottomY = (borderSpacing + barArea * i + barSpacing);
            channel.topY = (channel.bottomY + barWidth);
            mainAxisY.append(channel.meas.cellChannel + " - " + channel.meas.cellId, channel.topY + barSpacing / 2);
            channel.update();
        }
    }
}
