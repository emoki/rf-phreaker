import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelBarLine
    property ValueAxis mainAxisX
    property AreaSeries areaSeriesSL
    property AreaSeries areaSeriesInter
    property GenericMeasurement meas
    property real bottomY
    property real topY

    function update() {
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

//        var slPoints = [{x: startX, y: meas.carrierSignalLevel}, {x: stopX, y: meas.carrierSignalLevel}];
//        areaSeriesLower.upperSeries.replace(slPoints);
//        var interPoints = [{x: startX, y: meas.cellInterference}, {x: stopX, y: meas.cellInterference}];
//        areaSeries.upperSeries.replace(interPoints);
    }

    Connections {
        target: meas
        onCellSignalLevelChanged: update()
        onCellInterferenceChanged: update()
    }
}
