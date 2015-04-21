import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import RfPhreaker 1.0


Item {
    implicitWidth: 300
    implicitHeight: 240
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        TableView {
            id: collectionList
            Layout.fillHeight: true
            Layout.fillWidth: true
            alternatingRowColors: true
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

            TableViewColumn {
                id: techBandColumn
                horizontalAlignment: Text.AlignHCenter
                title: "Tech/Band"
                role: "techBand"
                width: 80
            }
            TableViewColumn {
                horizontalAlignment: Text.AlignHCenter
                title: "Frequency Range"
                role: "freqs"
                width: (collectionList.viewport.width - techBandColumn.width)  * 0.5
            }
            TableViewColumn {
                horizontalAlignment: Text.AlignHCenter
                title: "Channel Range"
                role:  "channels"
                width: (collectionList.viewport.width - techBandColumn.width) * 0.5
            }

            model: Api.collectionList.list
        }
        SuggestionTextField {
            id: collectionInfoSuggestionText

            Layout.fillWidth: true
            placeholderText: "Input band, channel, or frequency here."

            sSearch: search
            sView: collectionInfoSuggestions


            function doSelectionAction(item) {
                console.debug("Updating rpCollectionInfoList with ", selectedItem);
                Api.collectionList.append(selectedItem);
            }
        }
    }
    SuggestionView {
        id: collectionInfoSuggestions

        suggestionModel: search.results
        sTextField: collectionInfoSuggestionText

        anchors.bottom: columnLayout.bottom
        anchors.bottomMargin: collectionInfoSuggestionText.height
        Layout.fillWidth: true

        TableViewColumn {
            horizontalAlignment: Text.AlignHCenter
            title: "Tech/Band"
            role: "techBand"
            width: 100
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
