import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: channelSweepLine
    property LineSeries lineSeries
    property GenericMeasurement meas
    property alias sourceModel: filter.sourceModel
    property int bandwidth: 0;

    function refresh() {
        //console.debug("sweep channel bandwidth: ", filter.lowFreqFilter, " - ", filter.highFreqFilter);
        if(bandwidth < meas.carrierBandwidth) {
            bandwidth = meas.carrierBandwidth;
            filter.lowFreqFilter = meas.carrierFreq - meas.carrierBandwidth / 2;
            filter.highFreqFilter = meas.carrierFreq + meas.carrierBandwidth / 2;
            filter.reset();

            // This ensures we refresh the entire sweep line!

            //if(filter.sourceModel)
            //    filter.sourceModel.resetInternalData();

            //console.debug("sweep channel bandwidth: ", filter.lowFreqFilter, " - ", filter.highFreqFilter);
        }
    }

    FilterProxyMeasurementModel {
        id: filter
        filterRole: FilterProxyMeasurementModel.FreqRangeFilter
        lowFreqFilter: meas.carrierFreq - meas.carrierBandwidth / 2
        highFreqFilter: meas.carrierFreq + meas.carrierBandwidth / 2
    }

    VXYModelMapper {
        id: mapper
        model: filter
        series: lineSeries
        xColumn: MeasurementModel.CarrierFreqColumn
        yColumn: MeasurementModel.CarrierSignalLevelColumn
    }

    Connections {
        target: meas
        onCellSignalLevelChanged: {
            if(sourceModel === null) {
                lineSeries.clear();
                lineSeries.append(meas.carrierFreq - (meas.carrierBandwidth / 2), meas.carrierSignalLevel);
                lineSeries.append(meas.carrierFreq + (meas.carrierBandwidth / 2), meas.carrierSignalLevel);
            }
//            else
//                refresh();
        }
        onCarrierBandwidthChanged: {
            refresh();
        }
    }
}
