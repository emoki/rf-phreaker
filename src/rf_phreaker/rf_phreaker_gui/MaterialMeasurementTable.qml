import QtQuick 2.6
import Material 0.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0

Rectangle {
    id: root
    property alias tableView: dataTable
    property alias sourceModel: filter.sourceModel
    property alias filteredModel: dataTable.model
    property alias columnCount: dataTable.columnCount


    signal filteredModelUpdated()
    signal tableViewCompleted()

    implicitWidth: dp(96) * 9 + dp(64) * 4
    implicitHeight: Math.max(4, filter.rowCount()) * dp(48) + dp(16) + dp(56)

    function removeAllColumns() {
        while(dataTable.columnCount) {
            dataTable.removeColumn(0);
        }
    }

    function insertColumn(role, isString, index) {
        var idx = dataTable.model.findRole(role);
        var title = dataTable.model.headerData(0, 0, idx);
        console.debug("insert ", role, isString, index, root.tableView, idx, title);
        dataTable.insertColumn(index, columnComponent.createObject(dataTable, {"role": role, "title": title, "isString": isString, "_control": dataTable}));
    }

    function sortAndUpdate(tableColumn, sortOrder) {
        var column = dataTable.getColumn(tableColumn);
        if(column !== null && column.role !== null) {
            filter.sort(dataTable.model.convertRoleToColumn(column.role), sortOrder);
            root.filteredModelUpdated();
        }
    }

    Controls.TableView {
        id: dataTable

        anchors.fill: parent

        Component.onCompleted: tableViewCompleted()


        backgroundVisible: true
        sortIndicatorVisible: true
        frameVisible: false
        headerVisible: true
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        headerDelegate: MaterialHeaderDelegate { control: dataTable; }

        rowDelegate: MaterialRowDelegate{ control: dataTable; }

        model: FilterProxyMeasurementModel {
            id: filter
            filterRole: FilterProxyMeasurementModel.TimeFilter
            dynamicSortFilter: false // Must be set to false if we want to manually sort.
            expirationTimeFilter: GuiSettings.measurementRemovalTime
            Component.onCompleted: root.sortAndUpdate(dataTable.sortIndicatorColumn, dataTable.sortIndicatorOrder)
            onRowsInserted: {
                //console.debug("onRowsInserted")
                dataTable.implicitHeight = filter.rowCount() * dp(48) + dp(16) + dp(56)
                root.sortAndUpdate(dataTable.sortIndicatorColumn, dataTable.sortIndicatorOrder);
            }
        }
        Timer {
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                //console.debug("timer expired")
                filter.refilter();
                root.filteredModelUpdated();
            }
        }

        onSortIndicatorColumnChanged: root.sortAndUpdate(dataTable.sortIndicatorColumn, dataTable.sortIndicatorOrder)

        onSortIndicatorOrderChanged: root.sortAndUpdate(dataTable.sortIndicatorColumn, dataTable.sortIndicatorOrder)

        Controls.TableViewColumn {
            id: column0
            title: dataTable.model.headerData(0, 0, MeasurementModel.MeasurementFreqRole);
            role: "measurementFreq"
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellChannelRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellIdRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellSignalLevelRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellInterferenceRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellMccRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellMncRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellLacTacRole);
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
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellCidRole);
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

    Component {
        id: columnComponent
        Controls.TableViewColumn {
            property bool isString;
            property var _control;
            //width: dataTable.width / root.columnCount
            horizontalAlignment: Text.AlignRight;
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: _control;
                text: isString ? String(styleData.value) : Number(styleData.value).toFixed(1);
            }
            Component.onCompleted: console.debug("column ", role, title, isString, _control, delegate)
        }
    }
}
