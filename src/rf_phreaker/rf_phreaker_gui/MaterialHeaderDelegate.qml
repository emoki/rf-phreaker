import QtQuick 2.5
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls

Rectangle {
    property var control
    property alias tooltip: tip

    property alias text: label.text

    property alias action: actionItem.children
    property alias iconName: icon.name
    property alias iconSource: icon.source
    property alias secondaryItem: secondaryItem.children

    property alias itemLabel: label

    property alias textColor: label.color
    property alias iconColor: icon.color

    height: dp(56)
    implicitHeight: dp(56)

    ListItem.BaseListItem {
        id: listItem


        height: dp(56)
        implicitHeight: dp(56)
        margins: dp(24)
        showDivider: true

        dividerInset: 0

        implicitWidth: {
            var width = listItem.margins * 2

            if (actionItem.visible)
                width += actionItem.width + row.spacing

            if (sortIcon.visible)
                width += sortIcon.implicitWidth + row.spacing

            if (label.visible)
                width += label.width + row.spacing

            if (secondaryItem.visible)
                width += secondaryItem.width + row.spacing

            return width
        }

        RowLayout {
            id: row
            anchors.fill: parent
            anchors.leftMargin: listItem.margins
            anchors.rightMargin: listItem.margins

            spacing: 0 * Units.dp

            Rectangle {
                id: leftBuffer
                Layout.fillWidth: styleData.textAlignment === Qt.AlignRight
                Layout.preferredWidth: 0
            }

            Item {
                id: actionItem

                Layout.preferredWidth: 40 * Units.dp
                Layout.preferredHeight: width
                Layout.alignment: Qt.AlignCenter

                visible: children.length > 1 || icon.valid

                Icon {
                    id: icon

                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }

                    visible: valid
                    color: listItem.selected ? Theme.primaryColor : Theme.light.iconColor
                    size: 24 * Units.dp
                }
            }

            Item {
                id: sortIcon

                Layout.preferredWidth: 24 * Units.dp
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignVCenter

                opacity: visible ? 1 : 0
                visible: control.sortIndicatorVisible && styleData.column === control.sortIndicatorColumn

                Behavior on opacity {
                    NumberAnimation {
                        duration: 300; easing.type: Easing.InOutQuad
                    }
                }

                Icon {
                    anchors.verticalCenter: parent.verticalCenter
                    name: control.sortIndicatorVisible && styleData.column === control.sortIndicatorColumn
                          ?  "navigation/arrow_downward" : ""
                    size: dp(16)

                    rotation: control.sortIndicatorOrder === Qt.AscendingOrder ? 0 : 180

                    Behavior on rotation {
                        NumberAnimation { duration: 200 }
                    }
                }
            }

            Label {
                id: label

                Layout.alignment: Qt.AlignVCenter

                color: control.sortIndicatorVisible && styleData.column === control.sortIndicatorColumn
                       ? Theme.light.textColor : Theme.light.subTextColor

                elide: Text.ElideRight
                style: "body1"

                visible: text != ""

                text: styleData.value
            }

            Item {
                id: secondaryItem

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: childrenRect.width
                Layout.preferredHeight: parent.height

                visible: children.length > 0
            }

            Rectangle {
                id: rightBuffer
                Layout.fillWidth: styleData.textAlignment === Qt.AlignLeft
                Layout.preferredWidth: 0
            }

        }

        onClicked: {
            if(control.sortIndicatorVisible) {
                if(styleData.column === control.sortIndicatorColumn) {
                    control.sortIndicatorOrder = control.sortIndicatorOrder === Qt.AscendingOrder
                            ? Qt.DescendingOrder : Qt.AscendingOrder
                }
                else {
                    control.sortIndicatorColumn = styleData.Column
                }
            }
        }
    }
    Tooltip {
        id: tip
    }
}

//ListItem.Standard {
//    id: headerDelegate
//    property var view
//    property alias tooltip: tip

//    height: 56 * Units.dp
//    margins: 24 * Units.dp
//    implicitWidth: 100 * Units.dp
//    showDivider: true

//    valueText: styleData.value
//    itemValueLabel.color: view.sortIndicatorVisible && styleData.column === view.sortIndicatorColumn
//                          ? Theme.light.textColor : Theme.light.subTextColor

//    content: Rectangle {
//        anchors.centerIn: parent
//        width: 24 * Units.dp

//        Icon {
//            id: sortIcon
//            anchors.verticalCenter: parent.verticalCenter
//            name: view.sortIndicatorVisible && styleData.column === view.sortIndicatorColumn
//                  ?  "navigation/arrow_downward" : ""
//            size: dp(16)

//            rotation: view.sortIndicatorOrder === Qt.AscendingOrder ? 0 : 180

//            Behavior on rotation {
//                NumberAnimation { duration: 200 }
//            }
//        }
//    }

//    // Use dummy secondary item to push everything left if it is align left
//    secondaryItem: Rectangle {
//        width: 100 * Units.dp
//        visible: styleData.textAlignment === Qt.AlignLeft
//    }

//    onClicked: {
//        if(view.sortIndicatorVisible) {
//            if(styleData.column === view.sortIndicatorColumn) {
//                view.sortIndicatorOrder = view.sortIndicatorOrder === Qt.AscendingOrder
//                        ? Qt.DescendingOrder : Qt.AscendingOrder
//            }
//            else {
//                view.sortIndicatorColumn = styleData.Column
//            }
//        }
//    }

//    Tooltip {
//        id: tip
//    }
//}
