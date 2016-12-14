import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2

//Label {
//    Layout.fillWidth: true
//    verticalAlignment: Text.AlignVCenter
//    font.family: Flat.FlatStyle.fontFamily
//    font.pixelSize: textMenuPixelSize
//    renderType: Text.QtRendering
//}

Item {
    id: sideBarLabel
    property int iconSize: sideBarIconSize
    property int pixelSize: textMenuPixelSize
    property alias label: label_
    property alias text: label_.text
    property string defaultImageSource
    property string animatedSpriteSource
    property int componentIndex: 0
    property bool activated: true

    readonly property int defaultImageIndex: 0
    readonly property int busyIndicatorIndex: 1
    readonly property int animatedSpriteIndex: 2
    property var componentModel: [defaultImage, busyIndicator, animatedSprite]

    property Component defaultImage: Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: defaultImageSource
    }

    property Component busyIndicator: BusyIndicator {
        anchors.fill: parent
        running: true
    }

    property Component animatedSprite: AnimatedSprite {
        anchors.fill: parent
        source: animatedSpriteSource
        frameCount: 3
        frameWidth: 96
        frameHeight: 96
        loops: AnimatedSprite.Infinite
        interpolate: true
    }

    Behavior on opacity {
        NumberAnimation { duration: 1000 }
    }


    RowLayout {
        spacing: textMargins / 2
        anchors.fill: parent

        states: [
            State {
                when: sideBarLabel.activated;
                PropertyChanges {
                    target: sideBarLabel;
                    opacity: 1
                }
                PropertyChanges {
                    target: sideBarLabel;
                    visible: true
                }
            },
            State {
                when: !sideBarLabel.activated;
                PropertyChanges {
                    target: sideBarLabel;
                    opacity: 0
                }
                PropertyChanges {
                    target: sideBarLabel;
                    visible: false
                }
            }
        ]

        Loader {
            id: loader
            Layout.preferredWidth: iconSize
            Layout.preferredHeight: iconSize
            sourceComponent: componentModel[componentIndex]
        }

        Label {
            id: label_
            Layout.fillWidth: true
            verticalAlignment: Text.AlignVCenter
            font.family: Flat.FlatStyle.fontFamily
            font.pixelSize: pixelSize
            renderType: Text.QtRendering
        }
    }
}
