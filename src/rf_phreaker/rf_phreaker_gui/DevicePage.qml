import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import RfPhreaker 1.0

Rectangle {
    implicitHeight: 100
    implicitWidth: 50

    function setVisible(isVisible) {
        console.debug("devicePage visibility = ", isVisible);
        gpsLockStr.visible = isVisible;
        gpsUtcStr.visible = isVisible;
        trackingSatellitesStr.visible = isVisible;
    }

    GridLayout {
        Layout.fillWidth: true
        anchors.fill: parent
        Layout.minimumWidth: 100
        flow: GridLayout.LeftToRight
        columns: 2

        Label { text: "Status" }
        Label { id: statusStr; text: Api.statusStr; }
        Label { text: "Serial" }
        Label { id: serialStr; text: Api.connectedDevice.serial }
        Label { text: "GPS Lock" }
        Label { id: gpsLockStr; text: Api.gps.gpsLock }
        Label { text: "Universal Time Coordinate" }
        Label { id: gpsUtcStr; text: Api.gps.utcDateTime}
        Label { text: "Tracking Satellites" }
        Label { id: trackingSatellitesStr; text: Api.gps.trackingSatellites }
    }
}
