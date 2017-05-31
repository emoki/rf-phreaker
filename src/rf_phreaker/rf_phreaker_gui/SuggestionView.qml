import QtQuick 2.0
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1
import Material 0.3
import RfPhreaker 1.0

Controls.TableView {
    id: s

    property alias suggestionModel: s.model
    property var sTextField

    height: 400
    width: sTextField.width
    headerVisible: false
    alternatingRowColors: false
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    selectionMode: Controls.SelectionMode.SingleSelection

    signal close

    function sendCurrentSelection(row) {
        if(row !== -1) {
            //console.debug("Sending current selection (", suggestionModel[row], ".")
            sTextField.update(suggestionModel[row]);
        }
        close();
    }

    onClicked: sendCurrentSelection(row)
    onDoubleClicked: sendCurrentSelection(row)
}

