import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQml.Models 2.2
import QtQml.StateMachine 1.0 as DSM
import RfPhreaker 1.0

DSM.StateMachine {
    id: dsmOperation
    initialState: parentState
    running: true
    property bool recoverFromError

    signal connecting()
    signal connectScanner()
    signal disconnectScanner()
    signal updateLicense()
    signal startBackgroundScanning()
    signal startRecording()

    DSM.State {
        id: parentState
        initialState: smInitialize
        onFinished: console.debug("Statemachine finished!");
        onEntered: console.debug("Entered main state.")

        DSM.SignalTransition {
            signal: Api.errorMessage
            targetState: smError
        }
        DSM.SignalTransition {
            targetState: smChooseDevice
            signal: dsmOperation.connectScanner
        }

        DSM.State {
            id: smError
            onEntered: {
                console.debug("Entered smError.");
                Api.status = ApiTypes.ERROR
                Api.initializeApi();
                recoverFromError = true;
            }
            DSM.SignalTransition {
                signal: Api.apiInitialized
                targetState: smDisconnected
            }
        }

        DSM.State {
            id: smInitialize
            onEntered: {
                console.debug("Entered smInitialize.");
                Api.status = ApiTypes.DISCONNECTED;
                Api.initializeApi();
            }
            DSM.SignalTransition {
                signal: Api.apiInitialized
                targetState: smDisconnected
            }
        }

        DSM.State {
            id: smDisconnected
            initialState: smListingDevices
            onEntered: {
                console.debug("Entered smDisconnected.")
                Api.connectionStatus = ApiTypes.DISCONNECTED;
                Api.deviceStatus = ApiTypes.OFF;
            }

            DSM.State {
                id: smWait
                onEntered: console.debug("Entered smWait.")

                DSM.SignalTransition {
                    signal: dsmOperation.connectScanner
                    targetState: smListingDevices
                }
            }

            DSM.State {
                id: smListingDevices
                onEntered: {
                    console.debug("Entered smListingDevices.");
                    Api.listDevices();
                }
                DSM.SignalTransition {
                    targetState: smChooseDevice
                    signal: Api.numDevicesConnected
                    guard: numDevices > 0
                }
                DSM.TimeoutTransition {
                    timeout: 2000
                }
            }
            DSM.State {
                id: smChooseDevice
                onEntered: {
                    console.debug("Entered smChooseDevice.");
                    if(recoverFromError) {
                        console.debug("Recovering from error.  Looking for serial.")
                        var found = false;
                        for(var i = 0; i < Api.availableDevices.length; i++) {
                            if(Api.availableDevices[i] === Api.deviceSerial)
                                found = true;
                        }
                    }
                    console.debug("Serial found: ", found);
                    if(found) {
                        connecting();
                    }
                    else if(Api.availableDevices.length === 1) {
                        Api.deviceSerial = Api.availableDevices[0];
                        connecting();
                    }
                    else {
                        openScannerDialog.show();
                    }
                }
                DSM.SignalTransition {
                    targetState: smConnecting
                    signal: openScannerDialog.accepted
                }
                DSM.SignalTransition {
                    targetState: smConnecting
                    signal: connecting
                }
                DSM.SignalTransition {
                    targetState: smWait
                    signal: openScannerDialog.rejected
                }
            }
        }

        DSM.State {
            id: smConnecting
            onEntered: {
                console.debug("Entered smConnecting.");
                Api.connectionStatus = ApiTypes.CONNECTING;
                Api.deviceStatus = ApiTypes.OFF;
                Api.connectDevice(Api.deviceSerial);
                recoverFromError = false;
            }
            onExited: {
                console.debug("Leaving smConnecting.");
                //devicePage.setVisible(true);
            }

            DSM.SignalTransition {
                targetState: smIdle
                signal: Api.deviceConnected
            }
            DSM.SignalTransition {
                targetState: smDisconnected
                signal: Api.deviceDisconnected
            }
        }

        DSM.State {
            id: smConnected
            initialState: smIdle
            onEntered: {
                console.debug("Entered smIdle.")
                Api.connectionStatus = ApiTypes.CONNECTED;
            }
            DSM.SignalTransition {
                targetState: smWait
                signal: Api.deviceDisconnected
            }

            DSM.State {
                id: smIdle
                onEntered: {
                    console.debug("Entered smIdle.");
                    Api.deviceStatus = ApiTypes.IDLE;
                }
                onExited: {
                }

                DSM.SignalTransition {
                    targetState: smBackgroundScanning
                    signal: dsmOperation.startBackgroundScanning
                }
                DSM.SignalTransition {
                    targetState: smScanning
                    signal: dsmOperation.startScanning
                }
                DSM.SignalTransition {
                    targetState: smRecording
                    signal: dsmOperation.startRecording
                    guard: Api.collectionFilename !== ""
                }
            }
            DSM.State {
                id: smUpdatingLicense
                onEntered: {
                    console.debug("Entered smUpdatingLicense.");
                    Api.deviceStatus = ApiTypes.UPDATING_LICENSE;
                    Api.updateLicense();
                }
                onExited: {
                }
                DSM.SignalTransition {
                    targetState: smIdle
                    signal: Api.licenseUpdateSucceeded
                }
                DSM.SignalTransition {
                    targetState: smIdle
                    signal: Api.licenseUpdateFailed
                }
            }
            DSM.State {
                id: smScanning
                onEntered: {
                    console.debug("Entered smScanning.");
                    Api.deviceStatus = ApiTypes.SCANNING;
                    Api.startCollection();
                }
                onExited: {
                }
                DSM.SignalTransition {
                    targetState: smIdle
                    signal: Api.scanningStopped
                }
            }
            DSM.State {
                id: smBackgroundScanning
                onEntered: {
                    console.debug("Entered smBackgroundScanning.");
                    Api.deviceStatus = ApiTypes.BACKGROUND_SCANNING;
                    Api.startCollection();
                }
                onExited: {
                }
                DSM.SignalTransition {
                    targetState: smIdle
                    signal: Api.scanningStopped
                }
            }
            DSM.State {
                id: smRecording
                onEntered: {
                    console.debug("Entered smRecording.");
                    Api.deviceStatus = ApiTypes.RECORDING;
                    Api.openCollectionFile();
                    Api.startCollection();
                }
                onExited: {
                }
                DSM.SignalTransition {
                    targetState: smIdle
                    signal: Api.scanningStopped
                }
            }
        }
    }
}
