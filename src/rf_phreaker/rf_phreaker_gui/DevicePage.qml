import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import RfPhreaker 1.0

Rectangle {
    implicitHeight: 100
    implicitWidth: 50

    GridLayout {
        Layout.fillWidth: true
        anchors.fill: parent
        Layout.minimumWidth: 100
        columns: 2
        Label { text: "Status" }
        Label { text: Api.statusStr; }
        Label { text: "Serial" }
        Label { text: Api.connectedDevice.serial }
        Label { text: "GPS Lock" }
        Label { text: Api.gps.gpsLock }
        Label { text: "Universal Time Coordinate" }
        Label { text: Api.gps.utcDateTime}
        Label { text: "Tracking Satellites" }
        Label { text: Api.gps.trackingSatellites }
    }
}
