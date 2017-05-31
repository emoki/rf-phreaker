import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0
import Material 0.3

Item {
    id: channelBarLine
    property ChartView chart
    property ValueAxis mainAxisX
    property CategoryAxis mainAxisY
    property AreaSeries areaSeriesSL
    property AreaSeries areaSeriesInter
    property GenericMeasurement meas
    property real bottomY/*: (borderSpacing + barArea * index + barSpacing)*/
    property real topY/*: bottomY + barWidth*/
    property bool shouldUpdate: true
    property int index
    property string title: ""

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if(shouldUpdate) {
                update();
                shouldUpdate = false;
            }
        }
    }

    Label {
        id: label
        text: meas ? channelBarLine.title : ""
    }

    function update() {
        if(!visible)
            return;
        //console.debug("updating channelBarLine: ", meas.cellChannel, "-", meas.cellId);
        if(areaSeriesSL) {
            areaSeriesSL.upperSeries.clear();
            areaSeriesSL.upperSeries.append(mainAxisX.min, topY);
            areaSeriesSL.upperSeries.append(meas.cellSignalLevel, topY);
            areaSeriesSL.lowerSeries.clear();
            areaSeriesSL.lowerSeries.append(mainAxisX.min, bottomY);
            areaSeriesSL.lowerSeries.append(meas.cellSignalLevel, bottomY);
        }
        if(areaSeriesInter) {
            areaSeriesInter.upperSeries.clear();
            areaSeriesInter.upperSeries.append(meas.cellSignalLevel, topY);
            areaSeriesInter.upperSeries.append(meas.cellSignalLevel - meas.cellInterference, topY);
            areaSeriesInter.lowerSeries.clear();
            areaSeriesInter.lowerSeries.append(meas.cellSignalLevel, bottomY);
            areaSeriesInter.lowerSeries.append(meas.cellSignalLevel - meas.cellInterference, bottomY);
        }
        label.x = chart.plotArea.x
        label.y = chart.plotArea.y + ((topY + bottomY) / 2) / mainAxisY.max * chart.plotArea.height - label.height / 2

//        var slPoints = [{x: startX, y: meas.measurementSignalLevel}, {x: stopX, y: meas.measurementSignalLevel}];
//        areaSeriesLower.upperSeries.replace(slPoints);
//        var interPoints = [{x: startX, y: meas.cellInterference}, {x: stopX, y: meas.cellInterference}];
//        areaSeries.upperSeries.replace(interPoints);
    }

    Connections {
        target: meas
        onCellSignalLevelChanged: shouldUpdate = true;
        onCellInterferenceChanged: shouldUpdate = true;
    }
}
