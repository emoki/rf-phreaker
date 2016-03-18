import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelSweepLine
    property LineSeries lineSeries
    property GenericMeasurement meas
    property alias sourceModel: filter.sourceModel

    function refresh() {
        filter.invalidate();
        filter.lowFreqFilter = meas.carrierFreq - meas.carrierBandwidth / 2;
        filter.highFreqFilter = meas.carrierFreq + meas.carrierBandwidth / 2;
        filter.filterRole = FilterProxyMeasurementModel.FreqRangeFilter;
    }

    FilterProxyMeasurementModel {
        id: filter
        dynamicSortFilter: true
        filterRole: FilterProxyMeasurementModel.FreqRangeFilter
        lowFreqFilter: meas.carrierFreq - meas.carrierBandwidth / 2
        highFreqFilter: meas.carrierFreq + meas.carrierBandwidth / 2
    }

    VXYModelMapper {
        id: mapper
        model: filter
        //series: areaSeries.upperSeries
        series: lineSeries
        xColumn: MeasurementModel.CarrierFreqColumn
        yColumn: MeasurementModel.CarrierSignalLevelColumn
        Component.onCompleted: {
//            if(areaSeries && areaSeries.upperSeries)
//                series = areaSeries.upperSeries;
        }
    }

    Connections {
        target: meas
        onCellSignalLevelChanged: {
            if(sourceModel === null) {
                lineSeries.clear();
                lineSeries.append(meas.carrierFreq - (meas.carrierBandwidth / 2), meas.carrierSignalLevel);
                lineSeries.append(meas.carrierFreq + (meas.carrierBandwidth / 2), meas.carrierSignalLevel);
            }
        }
        onCarrierBandwidthChanged: {
            refresh();
        }
    }
}
