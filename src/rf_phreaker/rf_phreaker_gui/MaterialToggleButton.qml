import QtQuick 2.6
import Material 0.3
import Material.Extras 0.1
import QtQuick.Controls.Styles.Material 0.1 as MaterialStyle

Button {
    id: button
    style: MaterialStyle.ButtonStyle {
        radius: 0
    }

    property color checkedTextColor: "black"
    property color notCheckedColor: "darkgrey"
    property color checkedBackgroundColor: "lightgrey"
    property color notCheckedBackgroundColor: "transparent"
    checkable: true;
    backgroundColor: checked ? checkedBackgroundColor : notCheckedBackgroundColor
    textColor: checked ? checkedTextColor : notCheckedColor
}
