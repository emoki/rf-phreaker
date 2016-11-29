import QtQuick 2.5
import QtGraphicalEffects 1.0
import Material 0.3

Item {
    id: root

    property alias angle: rotation.angle
    property int posX: 0
    property int posY: 0

    width: 75
    height: 75
    x: posX - width * 0.5
    y: posY - height * 0.5

    transform: Rotation {
        id: rotation
        origin {
            x: root.width * 0.5
            y: root.height * 0.5
        }
    }

    Image {
        id: image
        source: "qrc:/icons/navigation_arrow_drop_up.svg"
        fillMode: Image.Stretch
        height: root.height * .40
        width: root.width * .40
        anchors.verticalCenterOffset: -innerCircle.width / 2 - 5
        anchors.centerIn: parent

        ColorOverlay {
                anchors.fill: image
                source: image
                color: Theme.primaryColor
        }
    }

    Rectangle {
        id: innerCircle
        width: root.width * .30
        height: root.height * .30
        color: Theme.primaryColor
        radius: width * .5
        anchors.centerIn: parent
    }


}
