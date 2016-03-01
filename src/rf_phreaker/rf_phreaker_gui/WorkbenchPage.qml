import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

ScrollView {
    id: scrollView
    anchors.fill: parent
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Flickable {
        anchors.fill: parent
        contentWidth: viewport.width

        GridLayout {
            id: mainGrid
            anchors.fill: parent
            anchors.margins: textMargins / 2
            columnSpacing: textMargins / 2
            rowSpacing: textMargins / 2
            columns: Math.max(1, Math.floor(scrollView.width / Math.max(scannerGroup.implicitWidth, gpsGroup.implicitWidth, licenses.implicitWidth)))


            Button {
                text: "Convert RFP file"
                enabled: true
                onClicked: {
                    fileDialog.open();
                }
            }
        }
    }
    property FileDialog fileDialog: FileDialog {
        id: fileDialog
        title: "Choose RFP file"
        nameFilters: [ "RF Phreaker files (*.rfp)", "All files (*)" ]
        selectMultiple: false
        sidebarVisible: true
        onAccepted: {
            Api.convertRfp(fileUrl);
        }
        onRejected: {
            console.debug("Rpf file conversion cancelled.");
        }
    }
}
