import QtQuick 2.5
import QtQuick.Controls 1.3 as Controls
import QtQuick.Controls.Styles 1.3 as ControlStyles
import Material 0.3
import Material.Extras 0.1

Item {
    id: expansionButton
    property bool expanded: false
    property alias color: icon.color
    property alias size: icon.size
    property string tooltipText

    implicitWidth: dp(44 + 8)
    implicitHeight: dp(44)

    signal clicked

    Item {
        id: expBut

        signal clicked

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -8 * Units.dp

        width: icon.width
        height: icon.height
        opacity: enabled ? 1 : 0.6

        Icon {
            id: icon
            anchors {
                centerIn: parent
            }

            name: "navigation/expand_more"
            rotation: expansionButton.expanded ? 180 : 0
            size: 24 * Units.dp

            Behavior on rotation {
                NumberAnimation { duration: 200 }
            }
        }
        onClicked: {
            expansionButton.expanded = !expansionButton.expanded
            expansionButton.clicked();
        }
        Ink {
            id: ink

            anchors.centerIn: parent
            enabled: expansionButton.enabled
            centered: true
            circular: true

            width: parent.width + 20 * Units.dp
            height: parent.height + 20 * Units.dp

            z: 0

            onClicked: {
                expBut.clicked()
            }
        }
    }
}

