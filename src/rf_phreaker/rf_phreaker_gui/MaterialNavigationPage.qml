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
            name: "open mr snacky, bitch!"
            onTriggered: snackbar.open("Test! test!!!")
        },
        Action {
            iconName: "maps/layers"
            name: "Manager layers"
            onTriggered: layerPopup.open()
        },
        Action {
            iconName: "file/file_download"
            name: "Download current map region"
            onTriggered: materialMarbleMap.marbleManager.downloadMapRegion(marbleManager.marbleMap)
        },
        Action {
            iconName: "navigation/more_vert"
            name: "More Options"
            hoverAnimation: true
        }
    ]
    PopupBase {
        id: layerPopup

        x: columnLayout.x + columnLayout.width / 2 - marblePlacemarkList.width / 2
        y: columnLayout.y + dp(64)

        width: marblePlacemarkList.implicitWidth
        height: marblePlacemarkList.implicitHeight

        globalMouseAreaEnabled: false
        dismissOnTap: false

        opacity: showing ? 1 : 0
        visible: opacity > 0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }

        View {
            id: dialogContainer

            anchors.fill: parent
            elevation: 5
            radius: dp(2)

            Flickable {
                id: viewFlick
                MaterialMarblePlacemarkList {
                    id: marblePlacemarkList
                    manager: materialMarbleMap.marbleManager
                    model: materialMarbleMap.marbleManager.placemarkModel
                    snackbar: page.snackbar
                    onClose: layerPopup.close()
                }
            }
            Scrollbar {
                flickableItem: viewFlick
            }
        }
    }
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

    Snackbar {
        id: snackbar
    }
}
