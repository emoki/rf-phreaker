import QtQuick 2.6
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0

Rectangle {
    id: root
    property alias sourceModel: filter.sourceModel
    property alias filteredModel: dataTable.model
    property int columnCount: 9

    signal filteredModelUpdated()

    implicitWidth: dp(96) * 9 + dp(64) * 4
    implicitHeight: Math.max(4, filter.rowCount()) * dp(48) + dp(16) + dp(56)

    //    height: 8 * dp(48) + dp(16) + dp(56)
//    width: dp(96) * 6 + dp(64) * 4


//    ColumnLayout {
//        anchors.fill: parent
//        clip:  true

    Controls.TableView {
        id: dataTable

        anchors.fill: parent

        backgroundVisible: true
        sortIndicatorVisible: true
        frameVisible: false
        headerVisible: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        headerDelegate: MaterialHeaderDelegate { control: dataTable; }

        rowDelegate: MaterialRowDelegate{ control: dataTable; }
//        rowDelegate: Rectangle {
//            height: dp(48);
//            width: dataTable.viewport.width
//            color: styleData.selected
//                             ? Palette.colors.grey[200]
//                             : Palette.colors.grey[100]
//        }

        model: FilterProxyMeasurementModel {
            id: filter
            filterRole: FilterProxyMeasurementModel.TimeFilter
            dynamicSortFilter: false // Must be set to false if we want to manually sort.
            expirationTimeFilter: 8
            Component.onCompleted: sortAndUpdate()
            onRowsInserted: {
                dataTable.implicitHeight = filter.rowCount() * dp(48) + dp(16) + dp(56)
                sortAndUpdate();
            }
        }
        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                //console.debug("timer expired")
                filter.refilter();
                filteredModelUpdated();
            }
        }

        function sortAndUpdate() {
            filter.sort(dataTable.convertColumn(dataTable.sortIndicatordicatorColumn), dataTable.sortIndicatorOrder)
            filteredModelUpdated();
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

        onSortIndicatorColumnChanged: sortAndUpdate()

        onSortIndicatorOrderChanged: sortAndUpdate()

        Controls.TableViewColumn {
            id: column0
            title: "Frequency"
            role: "carrierFreq"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: Number(styleData.value).toFixed(1)
            }
        }
        Controls.TableViewColumn {
            id: column1
            title: "Channel"
            role: "cellChannel"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: Number(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column2
            title: "Identifier"
            role: "cellId"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: Number(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column3
            title: "SL"
            role: "cellSignalLevel"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: Number(styleData.value).toFixed(1);
            }
        }
        Controls.TableViewColumn {
            id: column4
            title: "Interference"
            role: "cellInterference"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: Number(styleData.value).toFixed(1);
            }
        }
        Controls.TableViewColumn {
            id: column5
            title: "MCC"
            role: "mcc"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column6
            title: "MNC"
            role: "mnc"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column7
            title: "LAC/TAC"
            role: "lactac"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column8
            title: "CELLID"
            role: "cid"
            width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: dataTable
                text: String(styleData.value)
            }
        }
    }

}
