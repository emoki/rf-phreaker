import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

ColumnLayout {
    property alias text: label_.text
    property alias label: label_
    property alias source: image_.source
    property alias image: image_
    property real pixelSize: 25

    spacing: 0
    Layout.preferredHeight: 260
    Layout.alignment: Qt.AlignHCenter

    Image {
        id: image_
        fillMode: Image.PreserveAspectFit
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
    }
    Label {
        id: label_
        Layout.alignment: Qt.AlignCenter
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignTop | Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Flat.FlatStyle.fontFamily
        font.pixelSize: pixelSize
        renderType: Text.QtRendering
    }
}
