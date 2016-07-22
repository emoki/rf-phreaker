import QtQuick 2.5
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0

Item {
//    id: materialScanList
    property var scanList: Api.scanList
    property alias expanded: expBut.expanded

    implicitHeight: scanListView.implicitHeight + collectionInfoSuggestionText.implicitHeight

    ColumnLayout {
        id: layout
        anchors.fill: parent

        Controls.TableView {
            id: scanListView

            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitHeight: (scanList.list.length) * dp(48) + dp(16) + dp(56)

            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            selectionMode: Controls.SelectionMode.ExtendedSelection
            frameVisible: false
            backgroundVisible: true
            alternatingRowColors: false

            model: scanList.list

            headerDelegate: MaterialHeaderDelegate { view: scanListView }
            rowDelegate: MaterialRowDelegate{ view: scanListView }

//            Controls.TableViewColumn {
//                visible: !expanded
//                horizontalAlignment: Text.AlignLeft
//                title: "Type"
//                width: (scanListView.width - removeColumn.width) * .5
//                delegate: MaterialItemDelegate {
//                    property CollectionInfo ci: scanList.at(styleData)
//                    isNumber: false;
//                    view: scanListView
//                    text: ci.isSweep ? "Sweeping" : "Scanning"
//                }
//            }
//            Controls.TableViewColumn {
//                visible: !expanded
//                horizontalAlignment: Text.AlignRight
//                width: (scanListView.width - removeColumn.width) * .5
//                delegate: MaterialItemDelegate {
//                    property CollectionInfo ci: scanList.at(styleData)
//                    isNumber: true;
//                    view: scanListView
//                    text: ci.isSweep ? ci.band : ci.channels
//                }
//            }

            Controls.TableViewColumn {
                visible: expanded
                horizontalAlignment: Text.AlignLeft
                title: "Tech"
                role: "tech"
                width: (scanListView.width - removeColumn.width) * .25
                delegate: MaterialItemDelegate {
                    isNumber: false; view: scanListView
                }
            }
            Controls.TableViewColumn {
                visible: expanded
                horizontalAlignment: Text.AlignLeft
                title: "Band"
                role: "band"
                width: (scanListView.width - removeColumn.width) * .25
                delegate: MaterialItemDelegate { isNumber: false; view: scanListView }
            }
            Controls.TableViewColumn {
                visible: expanded
                horizontalAlignment: Text.AlignLeft
                title: "Frequency Range"
                role: "freqs"
                width: (scanListView.width - removeColumn.width) * .25
                delegate: MaterialItemDelegate { isNumber: false; view: scanListView }
            }
            Controls.TableViewColumn {
                visible: expanded
                horizontalAlignment: Text.AlignLeft
                title: "Channel Range"
                role:  "channels"
                width: (scanListView.width - removeColumn.width) * .25
                delegate: MaterialItemDelegate { isNumber: false; view: scanListView }
            }
            Controls.TableViewColumn {
                id: removeColumn
                horizontalAlignment: Text.AlignLeft
                width: dp(24 + 24) // extra 24 for margin
                delegate: MaterialItemDelegate {
                    view: scanListView
                    text: ""
                    iconName: "content/remove"
                    iconColor: Theme.light.textColor
                    margins: 0
                    dividerInset: 0
                    onClicked: { view.selection.clear(); scanList.remove(styleData.row); }
                }
            }

            Keys.onDeletePressed: {
                deleteItems();
            }

            function deleteItems() {
                var selectedItems = [];
                selection.forEach(function(rowIndex) { selectedItems.push(rowIndex); })
                selectedItems.reverse();
                selectedItems.forEach(function(item) { scanList.remove(item); })
            }
        }
        RowLayout {
//            SuggestionTextField {
//                id: collectionInfoSuggestionText

//                Layout.fillWidth: true

//                floatingLabel: false

//                placeholderText: "Input band, channel, or frequency here."

//                sSearch: search
//                sView: collectionInfoSuggestions

//                function doSelectionAction(item) {
//                    console.debug("Updating rpCollectionInfoList with ", selectedItem);
//                    scanList.append(selectedItem);
//                }

//                onClose: menu.close()
//                onOpen: {
//                    if(collectionInfoSuggestions.rowCount > 0 && menu.state === "closed") {
//                        menu.open(collectionInfoSuggestionText, 0, collectionInfoSuggestionText.height)
//                        collectionInfoSuggestions.currentRow = -1;
//                    }
//                }
//            }
            MaterialExpansionButton {
                id: expBut
            }
        }
//        Item {
//            id: dropTableView
//            Layout.alignment: Qt.AlignVCenter
//            Layout.fillWidth: true
//            property int maxVisibleItems: 4

//            Dropdown {
//                id: menu

//                anchor: Item.TopLeft
//                closeOnResize: false

//                width: dropTableView.width

//                //If there are more than max items, show an extra half item so
//                // it's clear the user can scroll
//                height: Math.min(dropTableView.maxVisibleItems*48 * Units.dp + 24 * Units.dp, (search.results.length) * 48 * Units.dp + dp(2))

//                SuggestionView {
//                    id: collectionInfoSuggestions
//                    property bool aboveSuggestionTextField: true

//                    anchors.fill:parent
//                    visible: menu.opacity === 1

//                    suggestionModel: search.results
//                    sTextField: collectionInfoSuggestionText

//                    rowDelegate: MaterialRowDelegate{ view: collectionInfoSuggestions }

//                    onClose: menu.close()

//                    Controls.TableViewColumn {
//                        horizontalAlignment: Text.AlignLeft
//                        title: "Tech"
//                        role: "tech"
//                        width: collectionInfoSuggestions.width * .25
//                        delegate: MaterialItemDelegate { isNumber: false; view: collectionInfoSuggestions }
//                    }
//                    Controls.TableViewColumn {
//                        horizontalAlignment: Text.AlignLeft
//                        title: "Band"
//                        role: "band"
//                        width: collectionInfoSuggestions.width * .25
//                        delegate: MaterialItemDelegate { isNumber: false; view: collectionInfoSuggestions }
//                    }
//                    Controls.TableViewColumn {
//                        horizontalAlignment: Text.AlignRight
//                        title: "Frequency Range"
//                        role: "freqs"
//                        width: collectionInfoSuggestions.width * .25
//                        delegate: MaterialItemDelegate { isNumber: false; view: collectionInfoSuggestions }
//                    }
//                    Controls.TableViewColumn {
//                        horizontalAlignment: Text.AlignRight
//                        title: "Channel Range"
//                        role:  "channels"
//                        width: collectionInfoSuggestions.width * .25
//                        delegate: MaterialItemDelegate { isNumber: false; view: collectionInfoSuggestions }
//                    }
//                }
//            }
//        }
    }
    CollectionInfoSearch {
        id: search
    }


}
