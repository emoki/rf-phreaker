
import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls

import Material 0.3
import Material.ListItems 0.1

Item {
    id: field

    implicitHeight: hasHelperText ? helperTextLabel.y + helperTextLabel.height + 4 * Units.dp
                                  : underline.y + 8 * Units.dp
    implicitWidth: spinBoxContents.implicitWidth

    activeFocusOnTab: true

    property color accentColor: Theme.accentColor
    property color errorColor: "#F44336"

    property alias dropMenu: menu

    //property alias tableView: loader.sourceComponent

    property Component tableView

    property int modelRowCount

    property string textRole

    //readonly property string selectedText: (tableView.currentItem) ? tableView.currentItem.text : ""

    //property alias selectedIndex: tableView.currentRow
    property int maxVisibleItems: 4

    property alias placeholderText: fieldPlaceholder.text
    property alias helperText: helperTextLabel.text

    property bool floatingLabel: false
    property bool hasError: false
    property bool hasHelperText: helperText.length > 0

    readonly property rect inputRect: Qt.rect(spinBox.x, spinBox.y, spinBox.width, spinBox.height)

    signal itemSelected(int index)

    Ink {
        anchors.fill: parent
        onClicked: {
           // tableView.positionViewAtRow(tableView.currentRow, tableView.Center)
            //var offset = tableView.currentRow.itemLabel.mapToItem(menu, 0, 0)
            menu.updateHeight();
            menu.open(label, 0, 0/*-offset.y*/)
        }
    }

    Item {
        id: spinBox

        height: 24 * Units.dp
        width: parent.width

        y: {
            if(!floatingLabel)
                return 16 * Units.dp
            if(floatingLabel && !hasHelperText)
                return 40 * Units.dp
            return 28 * Units.dp
        }

        RowLayout {
            id: spinBoxContents

            height: parent.height
            width: parent.width + 5 * Units.dp

            Loader {
                id: label

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                text: ""//(tableView.currentItem) ? tableView.currentItem.text : ""
                style: "subheading"
                elide: Text.ElideRight
            }

            Icon {
                id: dropDownIcon

                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                Layout.preferredWidth: 24 * Units.dp
                Layout.preferredHeight: 24 * Units.dp

                name: "navigation/arrow_drop_down"
                size: 24 * Units.dp
            }
        }

        Dropdown {
            id: menu

            anchor: Item.TopLeft

            width: spinBox.width

            //If there are more than max items, show an extra half item so
            // it's clear the user can scroll
            height: 0

            function updateHeight() {
                menu.height = Math.min(maxVisibleItems*48 * Units.dp + 24 * Units.dp, modelRowCount * 48 * Units.dp + 24 * Units.dp)
                console.debug(maxVisibleItems, modelRowCount, menu.height)
            }
            Loader {
                id: loader;
                sourceComponent: tableView
                anchors.fill: parent
            }
        }
    }

    Label {
        id: fieldPlaceholder

        text: field.placeholderText
        visible: floatingLabel

        font.pixelSize: 12 * Units.dp

        anchors.bottom: spinBox.top
        anchors.bottomMargin: 8 * Units.dp

        color: Theme.light.hintColor
    }

    Rectangle {
        id: underline

        color: field.hasError ? field.errorColor : field.activeFocus ? field.accentColor : Theme.light.hintColor

        height: field.activeFocus ? 2 * Units.dp : 1 * Units.dp

        anchors {
            left: parent.left
            right: parent.right
            top: spinBox.bottom
            topMargin: 8 * Units.dp
        }

        Behavior on height {
            NumberAnimation { duration: 200 }
        }

        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }

    Label {
        id: helperTextLabel

        anchors {
            left: parent.left
            right: parent.right
            top: underline.top
            topMargin: 4 * Units.dp
        }

        visible: hasHelperText
        font.pixelSize: 12 * Units.dp
        color: field.hasError ? field.errorColor : Qt.darker(Theme.light.hintColor)

        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }
}

//import QtQuick 2.4
//import QtQuick.Layouts 1.1
//import QtQuick.Controls 1.4 as Controls

//import Material 0.3
//import Material.ListItems 0.1

//Item {
//    id: field

//    implicitHeight: hasHelperText ? helperTextLabel.y + helperTextLabel.height + 4 * Units.dp
//                                  : underline.y + 8 * Units.dp
//    implicitWidth: spinBoxContents.implicitWidth

//    activeFocusOnTab: true

//    property color accentColor: Theme.accentColor
//    property color errorColor: "#F44336"

//    property alias dropMenu: menu

//    //property alias tableView: loader.sourceComponent

//    property Component tableView

//    property int modelRowCount

//    property string textRole

//    //readonly property string selectedText: (tableView.currentItem) ? tableView.currentItem.text : ""

//    //property alias selectedIndex: tableView.currentRow
//    property int maxVisibleItems: 4

//    property alias placeholderText: fieldPlaceholder.text
//    property alias helperText: helperTextLabel.text

//    property bool floatingLabel: false
//    property bool hasError: false
//    property bool hasHelperText: helperText.length > 0

//    readonly property rect inputRect: Qt.rect(spinBox.x, spinBox.y, spinBox.width, spinBox.height)

//    signal itemSelected(int index)

//    Ink {
//        anchors.fill: parent
//        onClicked: {
//           // tableView.positionViewAtRow(tableView.currentRow, tableView.Center)
//            //var offset = tableView.currentRow.itemLabel.mapToItem(menu, 0, 0)
//            menu.updateHeight();
//            menu.open(label, 0, 0/*-offset.y*/)
//        }
//    }

//    Item {
//        id: spinBox

//        height: 24 * Units.dp
//        width: parent.width

//        y: {
//            if(!floatingLabel)
//                return 16 * Units.dp
//            if(floatingLabel && !hasHelperText)
//                return 40 * Units.dp
//            return 28 * Units.dp
//        }

//        RowLayout {
//            id: spinBoxContents

//            height: parent.height
//            width: parent.width + 5 * Units.dp

//            Loader {
//                id: label

//                Layout.fillWidth: true
//                Layout.alignment: Qt.AlignVCenter

//                text: ""//(tableView.currentItem) ? tableView.currentItem.text : ""
//                style: "subheading"
//                elide: Text.ElideRight
//            }

//            Icon {
//                id: dropDownIcon

//                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
//                Layout.preferredWidth: 24 * Units.dp
//                Layout.preferredHeight: 24 * Units.dp

//                name: "navigation/arrow_drop_down"
//                size: 24 * Units.dp
//            }
//        }

//        Dropdown {
//            id: menu

//            anchor: Item.TopLeft

//            width: spinBox.width

//            //If there are more than max items, show an extra half item so
//            // it's clear the user can scroll
//            height: 0

//            function updateHeight() {
//                menu.height = Math.min(maxVisibleItems*48 * Units.dp + 24 * Units.dp, modelRowCount * 48 * Units.dp + 24 * Units.dp)
//                console.debug(maxVisibleItems, modelRowCount, menu.height)
//            }
//            Loader {
//                id: loader;
//                sourceComponent: tableView
//                anchors.fill: parent
//            }
//        }
//    }

//    Label {
//        id: fieldPlaceholder

//        text: field.placeholderText
//        visible: floatingLabel

//        font.pixelSize: 12 * Units.dp

//        anchors.bottom: spinBox.top
//        anchors.bottomMargin: 8 * Units.dp

//        color: Theme.light.hintColor
//    }

//    Rectangle {
//        id: underline

//        color: field.hasError ? field.errorColor : field.activeFocus ? field.accentColor : Theme.light.hintColor

//        height: field.activeFocus ? 2 * Units.dp : 1 * Units.dp

//        anchors {
//            left: parent.left
//            right: parent.right
//            top: spinBox.bottom
//            topMargin: 8 * Units.dp
//        }

//        Behavior on height {
//            NumberAnimation { duration: 200 }
//        }

//        Behavior on color {
//            ColorAnimation { duration: 200 }
//        }
//    }

//    Label {
//        id: helperTextLabel

//        anchors {
//            left: parent.left
//            right: parent.right
//            top: underline.top
//            topMargin: 4 * Units.dp
//        }

//        visible: hasHelperText
//        font.pixelSize: 12 * Units.dp
//        color: field.hasError ? field.errorColor : Qt.darker(Theme.light.hintColor)

//        Behavior on color {
//            ColorAnimation { duration: 200 }
//        }
//    }
//}
