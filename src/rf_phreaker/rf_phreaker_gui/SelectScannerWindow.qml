import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQuick.Window 2.2
import RfPhreaker 1.0

Window {
    id: openScannerWindow
    width: 16*20
    height: 10*20
    title: "Connect Scanner"
    signal canceled()
    signal accepted()

    flags: Qt.Dialog
    modality: Qt.WindowModal

    function highlighSerial() {
        var idx = 0;
        for(var i = 0; i < scannerList.rowCount; i++) {
            console.debug(scannerList.selection[i], " ", Api.deviceSerial);
            if(scannerList.selection[i] === Api.deviceSerial) {
                idx = i;
                break;
            }
        }
        scannerList.selection.select(idx);
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: textMargins / 2

        TableView {
            id: scannerList
            Layout.fillHeight: true
            Layout.fillWidth: true
            frameVisible: false
            backgroundVisible: true
            alternatingRowColors: false
            headerVisible: true
            model: Api.availableDevices
            selectionMode: SelectionMode.SingleSelection
            focus: true

            states: [
                State {
                    name: "showing"
                    when: visible
                    StateChangeScript {
                        script: {
                            var idx = 0;
                            console.debug("Visible changed!");
                            for(var i = 0; i < scannerList.rowCount; i++) {
                                console.debug("hello", scannerList.model[i], " ", Api.deviceSerial);
                                if(scannerList.model[i] === Api.deviceSerial) {
                                    idx = i;
                                    break;
                                }
                            }
                            scannerList.selection.select(idx);
                        }
                    }
                },
                State { name: "hidden"; when: !visible }
            ]

            Keys.onPressed: {
                if(event.key === Qt.Key_Return) {
                    console.debug("Found return key.")
                    openButton.clicked();
                    event.accepted = true;
                }
            }

            onDoubleClicked: {
                openButton.clicked();
            }

            TableViewColumn {
                role: modelData
                title: "Scanner Serial"
                width: scannerList.width
            }
        }
        RowLayout {
            Layout.alignment: Qt.RightToLeft
            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle {
                Layout.fillWidth: true
            }
            Button {
                text: "Cancel"
                Layout.alignment: Qt.AlignTop
                isDefault: !openButton.isDefault
                onClicked: {
                    canceled();
                    openScannerWindow.close()
                }
            }
            Button {
                id: openButton
                text: "Open Scanner"
                isDefault: true
                Layout.alignment: Qt.AlignTop
                enabled: scannerList.currentRow !== -1
                onClicked: {
                    Api.deviceSerial = scannerList.model[scannerList.currentRow];
                    accepted();
                    openScannerWindow.close()
                }
            }
        }
    }
}

