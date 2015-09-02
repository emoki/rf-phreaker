import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQml.StateMachine 1.0 as DSM
import RfPhreaker 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 1200
    height: 600

    DSM.StateMachine {
        id: dsmOperation
        initialState: smDisconnected
        running: true

        DSM.State {
            id: smDisconnected
            onEntered: {
                console.debug("Entered smDisconnected.");
                Api.status = ApiTypes.DISCONNECTED;
                devicePage.setVisible(false);
                Api.listDevices();
            }
            DSM.SignalTransition {
                id: smDisconnectedst1
                targetState: smChooseDevice
                signal: Api.numDevicesConnected
                guard: numDevices > 1
            }
            DSM.SignalTransition {
                id: smDisconnectedst2
                targetState: smConnecting
                signal: Api.numDevicesConnected
                guard: numDevices === 1
            }
            DSM.TimeoutTransition {
                id: smDisconnectedst3
                targetState: smDisconnected
                timeout: 2000
            }
        }
        DSM.State {
            id: smChooseDevice
            onEntered: {
                console.debug("Entered smChooseDevice.");

            }
            DSM.SignalTransition {
                targetState: smConnecting
            }
        }
        DSM.State {
            id: smConnecting
            onEntered: {
                console.debug("Entered smConnecting.");
                Api.status = ApiTypes.CONNECTING;
                Api.connectDevice();
            }
            onExited: {
                console.debug("Leaving smConnecting.");
                devicePage.setVisible(true);
            }

            DSM.SignalTransition {
                id: smConnectingst1
                targetState: smIdle
                signal: Api.deviceConnected
            }
            DSM.SignalTransition {
                id: smConnectingst2
                targetState: smDisconnected
                signal: Api.deviceDisconnected
            }
        }
        DSM.State {
            id: smIdle
            onEntered: {
                console.debug("Entered smIdle.");
                Api.status = ApiTypes.IDLE;
                startCollection.visible = true;
                startCollection.enabled = Api.collectionList.count() > 0;
            }
            onExited: {
                startCollection.enabled = false;
            }

            DSM.SignalTransition {
                id: smIdlest1
                targetState: smScanning
                signal: Api.scanningStarted
            }
            DSM.SignalTransition {
                id: smIdlest2
                targetState: smDisconnected
                signal: Api.deviceDisconnected
            }
            DSM.TimeoutTransition {
                targetState: smIdle
                timeout: 500
            }
        }
        DSM.State {
            id: smScanning
            onEntered: {
                console.debug("Entered smRecording.");
                Api.status = ApiTypes.RECORDING;
                startCollection.visible = false;
                stopCollection.visible = true;
            }
            onExited: {
                startCollection.visible = true;
                stopCollection.visible = false;
            }
            DSM.SignalTransition {
                id: smScanningst1
                targetState: smIdle
                signal: Api.scanningStopped
            }
            DSM.SignalTransition {
                id: smScanningst2
                targetState: smDisconnected
                signal: Api.deviceDisconnected
            }
        }
    }
    SplitView {
        id: splitView
        orientation: Qt.Vertical
        anchors.fill: parent
        GridLayout {
            columnSpacing: 0
            width: parent.width
            Rectangle {
                Layout.row: 0
                height: 30
                implicitWidth: 300
                Button {
                    id: startCollection
                    anchors.fill: parent
                    visible: true
                    enabled: false
                    text: "Start Scanning"
                    onClicked: Api.startCollection()
                }
                Button {
                    id: stopCollection
                    anchors.fill: parent
                    visible: false
                    text: "Stop Scanning"
                    onClicked: Api.stopCollection()
                }
            }

            DevicePage {
                id: devicePage
                Layout.row: 1
                height: 70
            }
            ChannelList {
                Layout.row: 2
            }
            SplitView {
                Layout.row: 0
                Layout.column: 2
                Layout.rowSpan: 3
                Layout.fillHeight: true
                Layout.fillWidth: true
                orientation: Qt.Vertical

                TableView {
                    id: umtsList
                    height: parent.height / 2
                    width: parent.width
                    model: Api.wcdmaList
                    TableViewColumn {
                        title: "Freq"
                        role: "carrierFreq"
                    }
                    TableViewColumn {
                        title: "UARFCN"
                        role: "uarfcn"
                    }
                    TableViewColumn {
                        title: "CPICH"
                        role: "cpich"
                    }
                    TableViewColumn {
                        title: "Ec/Io"
                        role: "ecio"
                    }
                    TableViewColumn {
                        title: "RSCP"
                        role: "rscp"
                    }
                }
                TableView {
                    id: lteList
                    height: parent.height / 2
                    width: parent.width
                    model: Api.lteList
                    TableViewColumn {
                        title: "Freq"
                        role: "carrierFreq"
                    }
                    TableViewColumn {
                        title: "EARFCN"
                        role: "earfcn"
                    }

                    TableViewColumn {
                        title: "Bandwidth"
                        role: "downlinkBandwidth"
                    }
                    TableViewColumn {
                        title: "PhysCellID"
                        role: "physicalCellID"
                    }
                    TableViewColumn {
                        title: "SyncQuality"
                        role: "syncQuality"
                    }
                    TableViewColumn {
                        title: "CarrierSL"
                        role: "carrierSignalLevel"
                    }
                }
            }
        }
        TableView {
            model: Api.log
            backgroundVisible: true
            selectionMode: SelectionMode.NoSelection
            headerVisible: false
            Layout.fillHeight: false
            TableViewColumn {
                role: "modelData"
            }
        }
    }
}

