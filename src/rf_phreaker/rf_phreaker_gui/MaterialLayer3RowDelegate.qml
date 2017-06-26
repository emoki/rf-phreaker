import QtQuick 2.7
import QtQml 2.2
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0

Rectangle {
    id: _root
    property var control
    property var meas

    height: childrenRect.height
    implicitHeight: childrenRect.height

    Rectangle {
        id: spacer
        height: dp(48)
        anchors.right: parent.right
        anchors.left: parent.left
        color: meas !== undefined && meas.isSelected ? Palette.colors.grey[300] : "transparent"
    }

    Rectangle {
        id: details
        visible: meas !== undefined && meas.isSelected
        anchors.top: spacer.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: meas !== undefined && meas.isSelected ? dp(350) : 0
        color: Palette.colors.grey[300]

        RowLayout {
            id: l3Layout
            anchors.fill: parent
            anchors.leftMargin: dp(16)
            anchors.rightMargin: dp(16)
            spacing: dp(0)

            ListView {
                id: layer3
                property int layer3ItemHeight: 0
                property int layer3ItemWidth: 0
                Layout.fillHeight: true
                Layout.bottomMargin: dp(16)
                Layout.preferredWidth: contentItem.childrenRect.width + dp(16)
                model: meas !== undefined ? meas.rawLayer3 : null
                highlightFollowsCurrentItem: false
                clip: true
                keyNavigationEnabled: true
                focus: true

                highlight: Rectangle {
                    color: Palette.colors.grey[400];
                    width: layer3.layer3ItemWidth
                    height: layer3.layer3ItemHeight
                    y: layer3.currentItem.y
                }

                delegate: Rectangle {
                    id: layer3Rect
                    height: layer3Message.contentHeight + dp(8)
                    width: layer3Message.contentWidth + dp(16)
                    color: "transparent"
                    Component.onCompleted: {
                        if(layer3.layer3ItemHeight < height)
                            layer3.layer3ItemHeight = height;
                        if(layer3.layer3ItemWidth < width)
                            layer3.layer3ItemWidth = width;
                    }

                    Label {
                        id: layer3Message
                        anchors.fill: parent
                        anchors.leftMargin: dp(8)
                        verticalAlignment: Text.AlignVCenter
                        text: messageType
                        MouseArea {
                            anchors.fill: parent
                            onClicked: layer3.currentIndex = index;
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: Palette.colors.grey[200];
                Flickable {
                    id: flick
                    anchors.fill: parent
                    anchors.bottomMargin: dp(16)
                    contentWidth: contentItem.childrenRect.width
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    Label {
                        id: description
                        anchors.top:  parent.top
                        anchors.left: parent.left
                        anchors.leftMargin: dp(16)
                        anchors.topMargin: dp(16)
                        anchors.bottomMargin: dp(16)
                        height: contentHeight
                        width: contentWidth
                        text: layer3.currentIndex != -1 ? layer3.model.data(layer3.model.index(layer3.currentIndex, 0), RawLayer3Model.DescriptionRole) : ""
                        onTextChanged: {
                            flick.contentX = 0;
                            flick.contentY = 0;
                        }
                    }
                }
            }
        }
    }
}
