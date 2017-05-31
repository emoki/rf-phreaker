import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1
import Material 0.3
import RfPhreaker 1.0


TextField {
    id: suggestionTextField

    property var sSearch
    property var sView
    property var selectedItem
    property alias filter: suggestionTextField.text
    property bool belowView: true

    signal close
    signal toggleOpen

    inputMethodHints: Qt.ImhNoPredictiveText || Qt.ImhPreferNumbers

    onFilterChanged: doSearch(filter)

    Keys.onUpPressed: {
        sView.currentRow--

        if(sView.currentRow < 0)
            sView.currentRow = sView.rowCount - 1;

        sView.selection.clear();
        sView.selection.select(sView.currentRow);
    }
    Keys.onDownPressed: {
        sView.currentRow++;

        if(sView.currentRow >= sView.rowCount)
            sView.currentRow = 0;

        sView.selection.clear();
        sView.selection.select(sView.currentRow);
    }
    Keys.onReturnPressed: {
        sView.sendCurrentSelection(sView.currentRow);
    }

    MouseArea {
        anchors.fill: parent
        onClicked: { toggleOpen(); suggestionTextField.forceActiveFocus(); }
        onDoubleClicked: { toggleOpen(); suggestionTextField.forceActiveFocus(); }
        propagateComposedEvents: true
    }

    function doSearch(text) {
        //console.debug("Searching for \"", text, "\".")
        sSearch.filter = text;
        sSearch.search();
        //console.debug("filter text: ", filter);
        toggleOpen();
    }

    function update(item) {
        //console.debug("Updating searchtextfield item. (clearing model)")
        selectedItem = item;
        filter = "";
        doSearch("");
        doSelectionAction();
    }
}

