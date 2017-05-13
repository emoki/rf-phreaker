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
        if(bandwidth < meas.measurementBandwidth) {
            bandwidth = meas.measurementBandwidth;
            filter.lowFreqFilter = meas.measurementFreq - meas.measurementBandwidth / 2;
            filter.highFreqFilter = meas.measurementFreq + meas.measurementBandwidth / 2;
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
        lowFreqFilter: meas.measurementFreq - meas.measurementBandwidth / 2
        highFreqFilter: meas.measurementFreq + meas.measurementBandwidth / 2
    }

    VXYModelMapper {
        id: mapper
        model: filter
        series: lineSeries
        xColumn: MeasurementModel.MeasurementFreqColumn
        yColumn: MeasurementModel.MeasurementSignalLevelColumn
    }

    Connections {
        target: meas
        onCellSignalLevelChanged: {
            if(sourceModel === null) {
                lineSeries.clear();
                lineSeries.append(meas.measurementFreq - (meas.measurementBandwidth / 2), meas.measurementSignalLevel);
                lineSeries.append(meas.measurementFreq + (meas.measurementBandwidth / 2), meas.measurementSignalLevel);
            }
//            else
//                refresh();
        }
        onMeasurementBandwidthChanged: {
            refresh();
        }
    }
}
