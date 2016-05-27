import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

Item {
    id: root
    property alias model: placemarkView.model
    property var manager

    GridLayout {
        id: grid
        anchors.fill: parent

        TableView {
            id: placemarkView
            Layout.row: 0
            Layout.columnSpan: 3
            Layout.fillWidth: true
            Layout.fillHeight: true
            selectionMode: SelectionMode.ExtendedSelection

            Keys.onDeletePressed: {
                deleteItems();
            }

            onDoubleClicked: { manager.centerOnPlacemark(currentRow); }

            function deleteItems() {
                var selectedItems = [];
                selection.forEach(function(rowIndex) { selectedItems.push(rowIndex); })
                selectedItems.reverse();
                selectedItems.forEach(function(row) { manager.removePlacemark(row); })
            }

            TableViewColumn {
                title: "Layer"
                width: placemarkView.viewport.width
                delegate: Item {
                    RowLayout {
                        CheckBox {
                            id: check
                            Layout.preferredWidth: 15
                            checked: Number(placemarkView.model.data(placemarkView.model.index(styleData.row, 0), MarbleProxyModel.CheckStateRole))
                            onClicked: {
                                manager.setPlacemarkGloballyVisible(styleData.row, check.checked);
                            }
                        }
                        Text {
                            Layout.fillWidth: true
                            text: String(placemarkView.model.data(placemarkView.model.index(styleData.row, 0), MarbleProxyModel.DisplayRole))
                        }
                    }
                }
            }
        }
        Item {
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
        }

        Button {
            Layout.row: 1
            Layout.column: 1
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            text: "Open"
            enabled: true
            onClicked: {
                openLayerDialog.open();
            }
        }

        Button {
            Layout.row: 1
            Layout.column: 2
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            text: "Delete"
            enabled: placemarkView.selection.count > 0
            onClicked: {
                placemarkView.deleteItems();
            }
        }
    }
    FileDialog {
        id: openLayerDialog
        visible: false
        title: "Choose the layers to open"
        nameFilters: [ "rf phreaker files (*.rfp)", "All files (*)" ]
        modality: Qt.WindowModal
        folder: shortcuts.documents
        selectedNameFilter: "rf phreaker files (*.rfp)"
        sidebarVisible: true
        selectExisting: true
        selectMultiple: true
        onAccepted: {
            console.log("Layers to open: " + fileUrls);
            for(var i = 0; i < fileUrls.length; ++i)
                manager.addRpf(fileUrls[i]);
        }
        onRejected: { console.log("Cancelled openLayers dialog.") }
    }
}
