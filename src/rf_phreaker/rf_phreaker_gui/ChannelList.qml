import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import RfPhreaker 1.0


Item {
    property var scanList
    property int bandColumnWidth: 140
    property alias suggestionViewHeight: collectionInfoSuggestions.height

    GridLayout {
        id: columnLayout
        anchors.fill: parent
        columns: 2
        columnSpacing: textMargins / 2
        rowSpacing: 0

        TableView {
            id: scanListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.columnSpan: 2
            alternatingRowColors: false
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            selectionMode: SelectionMode.ExtendedSelection
            frameVisible: true
            backgroundVisible: true


            TableViewColumn {
                id: techColumn
                horizontalAlignment: Text.AlignHCenter
                title: "Tech"
                role: "tech"
                width: (scanListView.width / 3) / 2
            }
            TableViewColumn {
                id: bandColumn
                horizontalAlignment: Text.AlignHCenter
                title: "Band"
                role: "band"
                width: (scanListView.width / 3) / 2
            }
            TableViewColumn {
                horizontalAlignment: Text.AlignHCenter
                title: "Frequency Range"
                role: "freqs"
                width: (scanListView.width / 3)
            }
            TableViewColumn {
                horizontalAlignment: Text.AlignHCenter
                title: "Channel Range"
                role:  "channels"
                width: (scanListView.width / 3)
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

            model: scanList.list
        }
        SuggestionTextField {
            id: collectionInfoSuggestionText

            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 0
            placeholderText: "Input band, channel, or frequency here."

            sSearch: search
            sView: collectionInfoSuggestions


            function doSelectionAction(item) {
                console.debug("Updating rpCollectionInfoList with ", selectedItem);
                scanList.append(selectedItem);
            }
        }
        Button {
            Layout.row: 1
            Layout.column: 1
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            text: "Delete"
            enabled: scanListView.selection.count > 0
            onClicked: {
                scanListView.deleteItems();
            }
        }
    }
    SuggestionView {
        id: collectionInfoSuggestions
        property bool aboveSuggestionTextField: false

        suggestionModel: search.results
        sTextField: collectionInfoSuggestionText

        anchors.top: !aboveSuggestionTextField ? columnLayout.bottom : undefined
        anchors.bottom: aboveSuggestionTextField ? columnLayout.bottom : undefined
        anchors.bottomMargin: aboveSuggestionTextField ? collectionInfoSuggestionText.height : undefined

        width: collectionInfoSuggestionText.width
        height: 200

        TableViewColumn {
            horizontalAlignment: Text.AlignHCenter
            title: "Tech"
            role: "tech"
        }
        TableViewColumn {
            horizontalAlignment: Text.AlignHCenter
            title: "Band"
            role: "band"
        }
        TableViewColumn {
            horizontalAlignment: Text.AlignHCenter
            title: "Frequency Range"
            role: "freqs"
        }
        TableViewColumn {
            horizontalAlignment: Text.AlignHCenter
            title: "Channel Range"
            role:  "channels"
        }
    }
    CollectionInfoSearch {
        id: search
    }
}
