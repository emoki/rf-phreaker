import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

TableView {
    id: dataWorksheet
    property alias sourceModel: filter.sourceModel
    property alias filteredModel: dataWorksheet.model
    property var columnCount: 9
    backgroundVisible: true
    sortIndicatorVisible: true
    frameVisible: false
    alternatingRowColors: false

    headerDelegate: Rectangle {
        height: textItem.implicitHeight * 1.2
        width: textItem.implicitWidth
        //color: "lightsteelblue"
        Text {
            id: textItem
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: styleData.value
            elide: Text.ElideRight
            //color: textColor
            renderType: Text.NativeRendering
        }
        Rectangle {
            anchors.top: textItem.bottom
            anchors.left: textItem.left
            anchors.right: textItem.right
            height: 1
            color: "#ccc"
        }
    }

    signal filteredModelUpdated()

    model: FilterProxyMeasurementModel {
        id: filter
        filterRole: FilterProxyMeasurementModel.NoFilterRole
        dynamicSortFilter: false
        Component.onCompleted: filter.sort(dataWorksheet.convertColumn(dataWorksheet.sortIndicatordicatorColumn), dataWorksheet.sortIndicatorOrder)
        onRowsInserted: {
//            console.debug("data worksheet filter model rows inserted");
//            filter.sort(dataWorksheet.convertColumn(dataWorksheet.sortIndicatorColumn), dataWorksheet.sortIndicatorOrder);
//            console.debug("data worksheet filter model after rows inserted");
            //filteredModelUpdated();
        }
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
            return MeasurementModel.CellMccColumn;
        case 6:
            return MeasurementModel.CellMncColumn;
        case 7:
            return MeasurementModel.CellLacTacColumn;
        case 8:
            return MeasurementModel.CellCidColumn;
        }
    }


    onSortIndicatorColumnChanged: {
        filter.sort(dataWorksheet.convertColumn(dataWorksheet.sortIndicatorColumn), dataWorksheet.sortIndicatorOrder);
        filteredModelUpdated();
    }
    onSortIndicatorOrderChanged: {
        filter.sort(dataWorksheet.convertColumn(dataWorksheet.sortIndicatorColumn), dataWorksheet.sortIndicatorOrder);
        filteredModelUpdated();
    }

    TableViewColumn {
        id: column0
        title: "Frequency"
        role: "basic"
        delegate: Text {
            text: Number(styleData.value.carrierFreq).toFixed(1)
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column1
        title: "Channel"
        role: "basic"
        delegate: Text {
            text: Number(styleData.value.cellChannel)
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column2
        title: "Identifier"
        role: "basic"
        delegate: Text {
            text: Number(styleData.value.cellId)
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column3
        title: "SL"
        role: "basic"
        delegate: Text {
            text: Number(styleData.value.cellSignalLevel).toFixed(1);
            horizontalAlignment: Text.AlignHCenter
        }
        width: (dataWorksheet.width / columnCount) * .8
    }
    TableViewColumn {
        id: column4
        title: "Interference"
        role: "basic"
        delegate: Text {
            text: Number(styleData.value.cellInterference).toFixed(1)
            horizontalAlignment: Text.AlignHCenter
        }
        width: (dataWorksheet.width / columnCount) * 1.2
    }
    TableViewColumn {
        id: column5
        title: "MCC"
        role: "basic"
        delegate: Text {
            text: styleData.value.cellMccStr
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column6
        title: "MNC"
        role: "basic"
        delegate: Text {
            text: styleData.value.cellMncStr
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column7
        title: "LAC/TAC"
        role: "basic"
        delegate: Text {
            text: styleData.value.cellLacTacStr
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
    TableViewColumn {
        id: column8
        title: "CellID"
        role: "basic"
        delegate: Text {
            text: styleData.value.cellCidStr
            horizontalAlignment: Text.AlignHCenter
        }
        width: dataWorksheet.width / columnCount
    }
}

//    SplitView {
//        anchors.fill: parent
//        orientation: Qt.Vertical

//        TableView {
//            id: umtsList
//            height: parent.height / 2
//            width: parent.width

//            model: FilterProxyMeasurementModel {
//                id: filter
//                sourceModel: Api.wcdmaFullScanModel
//                filterRole: FilterProxyMeasurementModel.NoFilterRole
//                dynamicSortFilter: false
//                Component.onCompleted: filter.sort(filter.convertColumn(umtsList.sortIndicatorColumn), umtsList.sortIndicatorOrder)
//                onRowsInserted: filter.sort(filter.convertColumn(umtsList.sortIndicatorColumn), umtsList.sortIndicatorOrder)
//            }

//            function convertColumn(column) {
//                switch(column) {
//                case 0:
//                    return MeasurementModel.CarrierFreqColumn;
//                case 1:
//                    return MeasurementModel.CellChannelColumn;
//                case 2:
//                    return MeasurementModel.CellIdColumn;
//                case 3:
//                    return MeasurementModel.CellSignalLevelColumn;
//                case 4:
//                    return MeasurementModel.CellInterferenceColumn;
//                }
//            }

//            sortIndicatorVisible: true
//            onSortIndicatorColumnChanged: filter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)
//            onSortIndicatorOrderChanged: filter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)

//            TableViewColumn {
//                title: "Freq"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.carrierFreq).toFixed(1)
//                }
//            }
//            TableViewColumn {
//                title: "UARFCN"
//                role: "basic"
//                delegate: Text {
//                    text: styleData.value.cellChannel
//                }
//            }
//            TableViewColumn {
//                title: "CPICH"
//                role: "basic"
//                delegate: Text {
//                    text: styleData.value.cellId
//                }
//            }
//            TableViewColumn {
//                title: "RSCP"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.cellSignalLevel).toFixed(1);
//                }
//            }
//            TableViewColumn {
//                title: "Ec/Io"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.cellInterference).toFixed(1)
//                }
//            }
//        }


//        TableView {
//            id: lteList
//            height: parent.height / 2
//            width: parent.width
//            model: FilterProxyMeasurementModel {
//                id: lteFilter
//                sourceModel: Api.lteFullScanModel
//                filterRole: FilterProxyMeasurementModel.NoFilterRole
//                dynamicSortFilter: false
//                Component.onCompleted: filter.sort(lteList.convertColumn(lteList.sortIndicatorColumn), lteList.sortIndicatorOrder)
//                onRowsInserted: filter.sort(lteList.convertColumn(lteList.sortIndicatorColumn), lteList.sortIndicatorOrder)
//            }

//            function convertColumn(column) {
//                switch(column) {
//                case 0:
//                    return MeasurementModel.CarrierFreqColumn;
//                case 1:
//                    return MeasurementModel.CellChannelColumn;
//                case 2:
//                    return MeasurementModel.CellIdColumn;
//                case 3:
//                    return MeasurementModel.CellSignalLevelColumn;
//                case 4:
//                    return MeasurementModel.CellInterferenceColumn;
//                case 5:
//                    return MeasurementModel.LteDownlinkBandwidthColumn;
//                }
//            }

//            sortIndicatorVisible: true
//            onSortIndicatorColumnChanged: lteFilter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)
//            onSortIndicatorOrderChanged: lteFilter.sort(convertColumn(sortIndicatorColumn), sortIndicatorOrder)

//            TableViewColumn {
//                title: "Freq"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.carrierFreq).toFixed(1)
//                }
//            }
//            TableViewColumn {
//                title: "EUARFCN"
//                role: "basic"
//                delegate: Text {
//                    text: styleData.value.cellChannel
//                }
//            }
//            TableViewColumn {
//                title: "PhysicalCID"
//                role: "basic"
//                delegate: Text {
//                    text: styleData.value.cellId
//                }
//            }
//            TableViewColumn {
//                title: "SyncSignalLevel"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.cellSignalLevel).toFixed(1);
//                }
//            }
//            TableViewColumn {
//                title: "SyncQuality"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.cellInterference).toFixed(1)
//                }
//            }
//            TableViewColumn {
//                title: "Bandwidth"
//                role: "basic"
//                delegate: Text {
//                    text: Number(styleData.value.carrierBandwidth).toFixed(1)
//                }
//            }
//        }
//    }
//}
