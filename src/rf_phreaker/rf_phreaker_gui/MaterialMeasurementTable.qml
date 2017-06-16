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
        dataTable.insertColumn(index, columnComponent.createObject(dataTable, {"role": role, "title": title, "isString": isString, "_control": dataTable}));
    }

    function sortAndUpdate(tableColumn, sortOrder) {
        var column = dataTable.getColumn(tableColumn);
        if(column !== null && column.role !== null) {
            var idxList = [];
            dataTable.selection.forEach(function(rowIndex) {
                idxList.push(filter.mapToSource(filter.index(rowIndex, 0)))
            });
            filter.sort(dataTable.model.convertRoleToColumn(column.role), sortOrder);
            dataTable.selection.clear();
            for(var i = 0; i < idxList.length; i++) {
                dataTable.selection.select(filter.mapFromSource(idxList[i]).row);
            }
            root.filteredModelUpdated();
        }
    }

    Controls.TableView {
        id: dataTable

        anchors.fill: parent

        Component.onCompleted: tableViewCompleted()

        backgroundVisible: false
        sortIndicatorVisible: true
        frameVisible: false
        headerVisible: true
        //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

        headerDelegate: MaterialHeaderDelegate { control: dataTable; }

        rowDelegate: MaterialLayer3RowDelegate {
            control: dataTable;
            Component.onCompleted: root.filteredModelUpdated.connect(update)
        }

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
            running: false
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
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: Number(styleData.value).toFixed(1)
            }
        }
        Controls.TableViewColumn {
            id: column1
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellChannelRole);
            role: "cellChannel"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: Number(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column2
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellIdRole);
            role: "cellId"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: Number(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column3
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellSignalLevelRole);
            role: "cellSignalLevel"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: Number(styleData.value).toFixed(1);
            }
        }
        Controls.TableViewColumn {
            id: column4
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellInterferenceRole);
            role: "cellInterference"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: Number(styleData.value).toFixed(1);
            }
        }
        Controls.TableViewColumn {
            id: column5
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellMccRole);
            role: "mcc"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column6
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellMncRole);
            role: "mnc"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column7
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellLacTacRole);
            role: "lactac"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column8
            title: dataTable.model.headerData(0, 0, MeasurementModel.CellCidRole);
            role: "cid"
            width: (dataTable.width  - dp(44)) / (root.columnCount - 1)
            horizontalAlignment: Text.AlignRight
            delegate: MaterialItemDelegate {
                isNumber: true;
                isSelectionEnabled: false
                control: dataTable
                text: String(styleData.value)
            }
        }
        Controls.TableViewColumn {
            id: column9
            width: dp(44)
            movable: false
            resizable: false
            delegate: Item {
                id: expDelegate
                width: expBut.width
                height: expBut.height
                Component.onCompleted: {
                    expBut.updateVisibility();
                    root.filteredModelUpdated.connect(expBut.updateVisibility);
                }
                MaterialExpansionButton {
                    id: expBut
                    anchors.top: parent.top
                    function updateVisibility() {
                        var meas = dataTable.model.data(dataTable.model.index(styleData.row, 0))
                        expBut.visible = meas ? meas.rawLayer3.rowCount() > 0 : false;
                        expBut.expanded = styleData.selected
                    }
                    onClicked: {
                        if(expBut.expanded)
                            dataTable.selection.select(styleData.row);
                        else
                            dataTable.selection.deselect(styleData.row);
                    }
                }
            }
        }
    }

    Component {
        id: columnComponent
        Controls.TableViewColumn {
            property bool isString;
            property var _control;
            property int fixedWidth: 1;
            horizontalAlignment: Text.AlignRight;
            delegate: MaterialItemDelegate {
                isNumber: true;
                control: _control;
                text: isString ? String(styleData.value) : Number(styleData.value).toFixed(fixedWidth);
            }
            Component.onCompleted: console.debug("column ", role, title, isString, _control, delegate)
        }
    }
}
