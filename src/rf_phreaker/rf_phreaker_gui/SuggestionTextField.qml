import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import RfPhreaker 1.0


TextField {
    id: suggestionTextField

    property var sSearch
    property var sView
    property var selectedItem
    property alias filter: suggestionTextField.text
    property bool belowView: true


    inputMethodHints: Qt.ImhNoPredictiveText || Qt.ImhPreferNumbers

    onFilterChanged: doSearch(filter)
    Keys.onUpPressed: {
        sView.focus = true;
        if(belowView)
            sView.currentRow = sView.rowCount - 1;
        else
            sView.currentRow = 0;
        sView.selection.select(sView.currentRow);
    }
    Keys.onDownPressed: {
        sView.focus = true;
        if(belowView)
            sView.currentRow = 0;
        else
            sView.currentRow = sView.rowCount - 1;
        sView.selection.select(sView.currentRow);
    }


    onActiveFocusChanged: {
        if(activeFocus || sView.activeFocus) {
            console.debug("suggestionTextField or View has focus!");
            doSearch(filter);
        }
        else {
            console.debug("suggestionTextField or View lost focus!");
            doSearch("");
        }

    }

    function doSearch(text) {
        console.debug("Searching for \"", text, "\".")
        sSearch.filter = text;
        sSearch.search();
        console.debug("filter text: ", filter);
    }

    function update(item) {
        console.debug("Updating searchtextfield item.")
        selectedItem = item;
        filter = "";
        doSearch("");
        doSelectionAction();
    }
}

