import QtQuick 2.5
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls

Rectangle {
    property var control
    height: childrenRect.height
    implicitHeight: childrenRect.height

//    ListItem.BaseListItem {
//        id: listItem
//        height: dp(48)
//        implicitHeight: dp(48)
//        margins: dp(24)
//        selected: styleData.selected
//        showDivider: false
//        backgroundColor: styleData.selected
//                         ? Palette.colors.grey[200]
//                         : Palette.colors.grey[100]

//        onClicked: {
//            if(control.selection.mode !== Controls.SelectionMode.NoSelection) {

//                if(control.selection.mode === Controls.SelectionMode.SingleSelection)
//                    control.selection.mode.clear();

//                if(control.selection.contains(styleData.row))
//                    control.selection.deselect(styleData.row)
//                else
//                    control.selection.select(styleData.row)
//            }
//            control.clicked(styleData.row);
//        }
//    }
    Item {
        id: spacer
        height: dp(48)
        anchors.right: parent.right
        anchors.left: parent.left
    }

    Rectangle {
        id: details
        visible: styleData.selected
        color: Palette.colors.grey[400];
        anchors.top: spacer.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: styleData.selected ? dp(140) : 0
    }
}
