import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import RfPhreaker 1.0

ScrollView {
    id: scannerScrollView
    anchors.fill: parent
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Flickable {
        anchors.fill: parent
        contentWidth: viewport.width

        GridLayout {
            anchors.fill: parent
            anchors.margins: textMargins / 2

            ChannelList {
                id: channelList
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                implicitHeight: parent.height * .65
                suggestionViewHeight: parent.height - channelList.height
                scanList: Api.scanList
            }
        }


    }
}
