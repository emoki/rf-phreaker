import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

Item {
    anchors.fill: parent

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        TableView {
            id: umtsList
            height: parent.height / 2
            width: parent.width

            model: FilterProxyMeasurementModel {
                id: filter
                sourceModel: Api.wcdmaFullScanModel
                filterRole: FilterProxyMeasurementModel.NoFilterRole
                dynamicSortFilter: false
                Component.onCompleted: filter.sort(filter.convertColumn(umtsList.sortIndicatorColumn), umtsList.sortIndicatorOrder)
                onRowsInserted: filter.sort(filter.convertColumn(umtsList.sortIndicatorColumn), umtsList.sortIndicatorOrder)
            }

            function convertColumn(column) {
                switch(column) {
                case 0:
                    return MeasurementModel.CarrierFreqColumn;
                case 1:
                    return MeasurementModel.CellChannelColumn;
                case 2:
                    return MeasurementModel.CellIdColumn;
                case 3:
                    return MeasurementModel.CellSignalLevelColumn;
                case 4:
                    return MeasurementModel.CellInterferenceColumn;
                }
            }

            sortIndicatorVisible: true
            onSortIndicatorColumnChanged: filter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)
            onSortIndicatorOrderChanged: filter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)

            TableViewColumn {
                title: "Freq"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.carrierFreq).toFixed(1)
                }
            }
            TableViewColumn {
                title: "UARFCN"
                role: "basic"
                delegate: Text {
                    text: styleData.value.cellChannel
                }
            }
            TableViewColumn {
                title: "CPICH"
                role: "basic"
                delegate: Text {
                    text: styleData.value.cellId
                }
            }
            TableViewColumn {
                title: "RSCP"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.cellSignalLevel).toFixed(1);
                }
            }
            TableViewColumn {
                title: "Ec/Io"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.cellInterference).toFixed(1)
                }
            }
        }
        TableView {
            id: lteList
            height: parent.height / 2
            width: parent.width
            model: FilterProxyMeasurementModel {
                id: lteFilter
                sourceModel: Api.lteFullScanModel
                filterRole: FilterProxyMeasurementModel.NoFilterRole
                dynamicSortFilter: false
                Component.onCompleted: filter.sort(lteList.convertColumn(lteList.sortIndicatorColumn), lteList.sortIndicatorOrder)
                onRowsInserted: filter.sort(lteList.convertColumn(lteList.sortIndicatorColumn), lteList.sortIndicatorOrder)
            }

            function convertColumn(column) {
                switch(column) {
                case 0:
                    return MeasurementModel.CarrierFreqColumn;
                case 1:
                    return MeasurementModel.CellChannelColumn;
                case 2:
                    return MeasurementModel.CellIdColumn;
                case 3:
                    return MeasurementModel.CellSignalLevelColumn;
                case 4:
                    return MeasurementModel.CellInterferenceColumn;
                case 5:
                    return MeasurementModel.LteDownlinkBandwidthColumn;
                }
            }

            sortIndicatorVisible: true
            onSortIndicatorColumnChanged: lteFilter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)
            onSortIndicatorOrderChanged: lteFilter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)

            TableViewColumn {
                title: "Freq"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.carrierFreq).toFixed(1)
                }
            }
            TableViewColumn {
                title: "EUARFCN"
                role: "basic"
                delegate: Text {
                    text: styleData.value.cellChannel
                }
            }
            TableViewColumn {
                title: "PhysicalCID"
                role: "basic"
                delegate: Text {
                    text: styleData.value.cellId
                }
            }
            TableViewColumn {
                title: "SyncSignalLevel"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.cellSignalLevel).toFixed(1);
                }
            }
            TableViewColumn {
                title: "SyncQuality"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.cellInterference).toFixed(1)
                }
            }
            TableViewColumn {
                title: "Bandwidth"
                role: "basic"
                delegate: Text {
                    text: Number(styleData.value.carrierBandwidth).toFixed(1)
                }
            }
        }
    }
}
