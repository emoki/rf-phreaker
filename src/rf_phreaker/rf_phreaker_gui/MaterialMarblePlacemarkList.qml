import QtQuick 2.6
import Material 0.3
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

Rectangle {
    id: materialPlacemarkView
    property alias model: placemarkView.model
    property var manager
    property var snackbar

    implicitHeight: Math.min(placemarkView.implicitHeight + toolbar.implicitHeight + dp(44), dp(676))
    implicitWidth: dp(676)

    signal close

    ColumnLayout {
        anchors {
            fill: parent
            topMargin: dp(16)
            rightMargin: dp(16)
            leftMargin: dp(16)
            bottomMargin: dp(16)
        }
        spacing: dp(16)

        RowLayout {
            id: toolbar
            Layout.fillWidth: true

            spacing: dp(8)
            Item { Layout.fillWidth: true }

            IconButton {
                    iconName: "content/add"
                    color: Theme.light.textColor
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: openLayerDialog.open()
                }
            IconButton {
                    iconName: "navigation/close"
                    color: Theme.light.textColor
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: materialPlacemarkView.close()
            }
        }

        Controls.TableView {
            id: placemarkView

            Layout.fillHeight: true
            Layout.fillWidth: true

            selectionMode: Controls.SelectionMode.NoSelection
            sortIndicatorVisible: false
            frameVisible: false

            function updateHeight() {
                if(placemarkView.model !== undefined)
                    placemarkView.implicitHeight = placemarkView.model.rowCount() * dp(48) + dp(56) + dp(15)
                else
                    placemarkView.implicitHeight = 4 * dp(48) + dp(56) + dp(15)
            }

            onVisibleChanged: placemarkView.updateHeight()
            Component.onCompleted: placemarkView.updateHeight()
            Connections {
                target: placemarkView.model
                onRowsInserted: placemarkView.updateHeight()
                onRowsRemoved: placemarkView.updateHeight()
            }

            // Integrate into item delegate!
            onDoubleClicked: { manager.centerOnPlacemark(currentRow); }

            headerDelegate: MaterialHeaderDelegate { control: placemarkView }

            rowDelegate: MaterialRowDelegate { control: placemarkView }

            Controls.TableViewColumn {
                id: layers
                title: "Layers"
                width: placemarkView.width - dp(64)
                delegate: MaterialItemDelegate {
                    control: placemarkView
                    action: Row {
                        CheckBox {
                            id: check
                            checked: Number(placemarkView.model.data(placemarkView.model.index(styleData.row, 0), MarbleProxyModel.CheckStateRole))
                            onClicked: {
                                manager.setPlacemarkGloballyVisible(styleData.row, check.checked);
                            }
                            text: {
                                var s = String(placemarkView.model.data(placemarkView.model.index(styleData.row, 0), MarbleProxyModel.DisplayRole))
                                var sub = s.split('/');
                                return sub[sub.length - 1]
                            }
                        }
                    }
                }
//                Tooltip {
//                    text: "Doubleclick to center on layer"
//                }
            }
            Controls.TableViewColumn {
                width: placemarkView.width - layers.width - dp(5)
                delegate: MaterialItemDelegate {
                    control: placemarkView
                    action: IconButton {
                        iconName: "content/remove"
                        color: Theme.light.textColor
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: manager.removePlacemark(styleData.row);
                        enabled: {
                            var s = String(placemarkView.model.data(placemarkView.model.index(styleData.row, 0), MarbleProxyModel.DisplayRole))
                            return s !== "Current Position" && s !== "Current Track" && s.indexOf("recording") === -1
                        }
                    }
                }
            }
        }
    }
    FileDialog {
        id: openLayerDialog
        visible: false
        title: "Choose layers"
        nameFilters: [ "rf phreaker files (*.rpf)", "kml files (*.kml)", "All files (*)" ]
        modality: Qt.WindowModal
        folder: shortcuts.documents
        selectedNameFilter: "rf phreaker files (*.rpf)"
        sidebarVisible: true
        selectExisting: true
        selectMultiple: true
        onAccepted: {
            console.log("Layers to import: " + fileUrls);
            for(var i = 0; i < fileUrls.length; ++i)
                manager.addLayer(fileUrls[i]);
        }
        onRejected: { console.log("Canceled openLayers dialog.") }
    }
}
