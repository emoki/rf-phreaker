import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import Material 0.3
import RfPhreaker 1.0

Dialog {
    id: openScannerDialog
    title: "Connect Scanner"

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

    negativeButtonText: "Cancel"

    positiveButtonText: "Open Scanner"

    dialogContent: ColumnLayout {
        anchors.fill: parent

        Controls.TableView {
            id: scannerList
            Layout.fillHeight: true
            Layout.fillWidth: true
            frameVisible: false
            backgroundVisible: true
            alternatingRowColors: false
            headerVisible: true
            model: Api.availableDevices
            selectionMode: Controls.SelectionMode.SingleSelection
            focus: true

            headerDelegate: MaterialHeaderDelegate { control: scannerList }
            rowDelegate: MaterialRowDelegate { control: scannerList }

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

            Controls.TableViewColumn {
                //role: modelData
                title: "Scanner Serial"
                width: scannerList.width
                horizontalAlignment: Text.AlignRight
                delegate: MaterialItemDelegate { isNumber: false; control: scannerList }
            }
        }
    }
}

