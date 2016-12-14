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

//    property real index: 0
//    property int totalNumBars
//    property real borderSpacing: ((mainAxisY.max - mainAxisY.min) / totalNumBars) / 6
//    property real barArea: (mainAxisY.max - mainAxisY.min - 2 * borderSpacing) / totalNumBars
//    property real barSpacing: barArea / 5
//    property real barWidth: barArea - barSpacing * 2

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
        text: meas ? " " + meas.cellChannel + " - " + (meas.cellId !== -1 ? meas.cellId : "N/A") : ""
    }

    function update() {
        if(!visible)
            return;
        //console.debug("updating channelBarLine: ", meas.cellChannel, "-", meas.cellId);
        areaSeriesSL.upperSeries.clear();
        areaSeriesSL.upperSeries.append(mainAxisX.min, topY);
        areaSeriesSL.upperSeries.append(meas.carrierSignalLevel, topY);
        areaSeriesSL.lowerSeries.clear();
        areaSeriesSL.lowerSeries.append(mainAxisX.min, bottomY);
        areaSeriesSL.lowerSeries.append(meas.carrierSignalLevel, bottomY);

        areaSeriesInter.upperSeries.clear();
        areaSeriesInter.upperSeries.append(meas.carrierSignalLevel, topY);
        areaSeriesInter.upperSeries.append(meas.carrierSignalLevel - meas.cellInterference, topY);
        areaSeriesInter.lowerSeries.clear();
        areaSeriesInter.lowerSeries.append(meas.carrierSignalLevel, bottomY);
        areaSeriesInter.lowerSeries.append(meas.carrierSignalLevel - meas.cellInterference, bottomY);

        label.x = chart.plotArea.x
        label.y = chart.plotArea.y + ((topY + bottomY) / 2) / mainAxisY.max * chart.plotArea.height - label.height / 2

//        var slPoints = [{x: startX, y: meas.carrierSignalLevel}, {x: stopX, y: meas.carrierSignalLevel}];
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
