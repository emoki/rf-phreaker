import QtQuick 2.5
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls

Rectangle {
    property var control
    property bool isNumber: true
    property alias tooltip: tip

    property alias text: listItem.text
    property alias valueText: listItem.valueText

    property alias action: listItem.action
    property alias iconName: listItem.iconName
    property alias iconSource: listItem.iconSource
    property alias secondaryItem: listItem.secondaryItem
    property alias content: listItem.content

    property alias itemLabel: listItem.itemLabel
    property alias itemValueLabel: listItem.itemValueLabel

    property alias textColor: listItem.textColor
    property alias iconColor: listItem.iconColor

    height: dp(48)
    implicitHeight: dp(48)

    ListItem.Standard {
        id: listItem

        height: dp(48)
        implicitHeight: dp(48)
        margins: dp(24)
        selected: styleData.selected
        showDivider: false
        dividerInset: 0
        text: styleData.value;
        itemLabel.horizontalAlignment: isNumber ? Qt.AlignRight : Qt.AlignLeft
        itemLabel.color: Theme.light.textColor

        backgroundColor: styleData.selected
                         ? Palette.colors.grey[200]
                         : Palette.colors.grey[100]

        onClicked: {
            if(control.selection.mode !== Controls.SelectionMode.NoSelection) {

                if(control.selection.mode === Controls.SelectionMode.SingleSelection)
                    control.selection.mode.clear;

                if(control.selection.contains(styleData.row))
                    control.selection.deselect(styleData.row)
                else
                    control.selection.select(styleData.row)
            }
            control.clicked(styleData.row);
        }

        // Implement mouse area for other clicks
        //onDoubleClicked: control.doubleClicked(styleData.row)
    }

    Tooltip {
        id: tip
    }
}
