import QtQuick 2.3
import QtCharts 2.1
import RfPhreaker 1.0

Item {
    id: sweepLine

    property MeasurementModel sourceModel
    property LineSeries lineSeries
    VXYModelMapper {
        id: mapper
        series: lineSeries
        model: sourceModel
        xColumn: MeasurementModel.CarrierFreqColumn
        yColumn: MeasurementModel.CarrierSignalLevelColumn
    }
}
