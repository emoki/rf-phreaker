import QtQuick 2.5
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0
import org.kde.edu.marble 0.20

Page {
    id: page

    title: "RF Phreaker Navigation"

    actions: [
        Action {
            iconName: "maps/layers"
            name: "Manage Layers"
            onTriggered: materialMarbleMap.layerPopup.open()
        },
        Action {
            iconName: "file/file_download"
            name: "Download Current Map"
            onTriggered: materialMarbleMap.marbleManager.downloadMapRegion()
        },
        Action {
            id: startRecording
            visible: Api.deviceStatus !== ApiTypes.RECORDING
            enabled: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.IDLE
            text: "Record Data"
            shortcut: "Ctrl+R"
            iconName: "av/play_arrow"
            onTriggered: {
                rpWindow.startCollectionDialog.filename = "collection_data_" +
                        Qt.formatDateTime(new Date(), "yyyy-MMM-dd_hh-mm-ss");
                rpWindow.startCollectionDialog.open()
            }
        },
        Action {
            id: stopRecording
            visible: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.RECORDING
            text: "Stop Recording"
            shortcut: "Ctrl+S"
            iconName: "av/stop"
            onTriggered: rpWindow.stateMachine.stopScanning()
        },
        Action {
            iconName: "navigation/more_vert"
            name: "More Options"
            hoverAnimation: true
        }
    ]

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"

            MaterialMarbleMap {
                id: materialMarbleMap
                anchors.fill: parent
                visible: true
            }
        }
    }

    MaterialMarbleLocationButton {
        marbleManager: materialMarbleMap.marbleManager
        anchors {
            right: parent.right
            //bottom: parent.bottom
            bottom: snackbar.top
            margins: dp(32)
        }
    }
}
