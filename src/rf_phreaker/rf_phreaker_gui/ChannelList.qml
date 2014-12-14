import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import RfPhreaker 1.0

Rectangle {
    id: channelList
    implicitHeight: 100
    implicitWidth: rowLayout.implicitWidth
    height: implicitHeight
    width: implicitWidth

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        RowLayout {
            id: rowLayout
            implicitWidth: comboBox.implicitWidth + userInput.implicitWidth

            ComboBox {
                id: comboBox
                implicitWidth: 75
                model: ["WCDMA", "LTE", "RawIQ"]
            }
                TextField {
                    implicitWidth: 150
                    Layout.fillWidth: true
                    id: userInput
                    placeholderText: "Input channel(s) or frequencies here."
                    Keys.onPressed: suggestionBox.visible = true
                }
        }

        TableView {
            id: freqChannels
            Layout.fillHeight: true
            Layout.fillWidth: true
            alternatingRowColors: true

            TableViewColumn {
                title: "Tech"
                width: comboBox.width
                role: model.tech
            }
            TableViewColumn {
                title: "Channel Range"
            }
            TableViewColumn {
                title: "Frequency Range"
            }

            //model: ["0", "1", "3"]
            model: rpChannelFreqList.channelFreqList
        }
    }
    TableView {
        id: suggestionBox
        visible: false
        headerVisible: false
        height: 150
        anchors.top: columnLayout.top
        anchors.topMargin: userInput.height
        anchors.left: columnLayout.left
        anchors.leftMargin: comboBox.width + rowLayout.spacing
        //anchors.right: columnLayout.right
        TableViewColumn {
            //role: channel
            title: "Channel Range"
        }
        TableViewColumn {
            //role: freq
            title: "Frequency Range"
        }
        model: ["0","1","2"]
        //model: rpChannelFreqList.channelFreqList
    }

    RpChannelFreqList {
        id: rpChannelFreqList
//        channelFreqList: [
//            RpChannelFreq {
//                id: rp3
//                channel: "2"
////                freq: "1962"
////                band: "UMTS_OPERATING_BAND_1"
////                tech: "WCDMA"
//            },
//            RpChannelFreq {
//                id: rp4
//                channel: "2"
////                freq: "1962"
////                band: "UMTS_OPERATING_BAND_1"
////                tech: "WCDMA"
//            }
//        ]
    }
}
