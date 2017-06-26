import QtQuick 2.6
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4 as Controls
import QtQuick.Dialogs 1.2
import RfPhreaker 1.0

Page {
    id: page
    title: "RF Phreaker Settings"
    property int cardWidth: dp(600)

    actions: [
        Action {
            name: "Convert RPF file to ASCII"
            iconName: "av/note"
            onTriggered: rpfConversionDialog.open();
        },
        Action {
            id: startRecording
            visible: Api.deviceStatus !== ApiTypes.RECORDING
            enabled: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.IDLE
            name: "Record Data"
            shortcut: "Ctrl+R"
            iconName: "av/play_circle_filled"
            onTriggered: {
                rpWindow.startCollectionDialog.filename = "collection_data_" +
                        Qt.formatDateTime(new Date(), "yyyy-MMM-dd_hh-mm-ss");
                rpWindow.startCollectionDialog.open()
            }
        },
        Action {
            id: stopRecording
            visible: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus === ApiTypes.RECORDING
            name: "Stop Recording"
            shortcut: "Ctrl+S"
            iconName: "av/stop"
            onTriggered: rpWindow.stateMachine.stopScanning()
        },
        Action {
            name: "Show Log"
            shortcut: "Ctrl+L"
            iconName: "action/subject"
            onTriggered: rpWindow.showLog()
        }
    ]

    Component.onDestruction: {
        page.apply()
    }

    function apply() {
        var reinit = GuiSettings.shouldReinitializeApi();
        GuiSettings.saveSettings();
        if(reinit)
            dsmOperation.reinitialize();
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.margins: dp(16)
        contentWidth: parent.width;
        contentHeight: layout.childrenRect.height
        flickableDirection: Flickable.VerticalFlick

        Column {
            id: layout
            anchors.horizontalCenter: parent.horizontalCenter
            width: page.cardWidth
            height: page.height
            spacing: dp(0)

            Item { height: dp(32); width: page.cardWidth }
            ListItem.Subheader { text: "General" }
            Card {
                width: page.cardWidth
                height: dataColumn.height
                Column {
                    id: dataColumn
                    width: parent.width
                    height: childrenRect.height
                    ListItem.Subtitled {
                        id: cProfile
                        text: "Collection profile"
                        subText: "Changes scan rate and decode parameters based on profile"
                        secondaryItem: MenuField {
                            id: cProfileMenu
                            anchors.centerIn: parent
                            implicitWidth: dp(16*9)
                            implicitHeight: parent.height
                            floatingLabel: false
                            maxVisibleItems: 6
                            model: ["Fast scan rate", "Prioritize layer 3"]
                            function setProfile(index) {
                                GuiSettings.setProfile(index);
                            }
                            Component.onCompleted: {
                                cProfileMenu.selectedIndex = GuiSettings.currentProfile
                                cProfileMenu.itemSelected.connect(setProfile)
                            }
                        }
                    }
                    ListItem.Subtitled {
                        id: graphRemoval
                        text: "Remove old measurements from graphs after"
                        secondaryItem: MenuField {
                            id: graphRemovalMenu
                            anchors.centerIn: parent
                            implicitWidth: dp(16*8)
                            implicitHeight: parent.height
                            model: [ "5 second", "15 seconds", "30 seconds", "1 minute", "5 minutes", "Never"]
                            floatingLabel: false
                            maxVisibleItems: 6
                            function setMeasurementRemovalTime(index) {
                                GuiSettings.measurementRemovalTime = graphRemovalMenu.convertIndex(index);
                            }
                            Component.onCompleted: {
                                graphRemovalMenu.selectedIndex = graphRemovalMenu.convertValue(GuiSettings.measurementRemovalTime)
                                graphRemovalMenu.itemSelected.connect(setMeasurementRemovalTime)
                            }
                            function convertValue(value) {
                                switch(value) {
                                case 5:
                                    return 0;
                                case 15:
                                    return 1;
                                case 30:
                                    return 2;
                                case 60:
                                    return 3;
                                case 60 * 5:
                                    return 4;
                                case -1:
                                    return 5;
                                // Default to one minute.
                                default:
                                    console.debug("invalid value for measurement removal time")
                                    return 3;
                                }
                            }
                            function convertIndex(index) {
                                switch(index) {
                                case 0:
                                    return 5;
                                case 1:
                                    return 15;
                                case 2:
                                    return 30;
                                case 3:
                                    return 60;
                                case 4:
                                    return 60 * 5;
                                case 5:
                                    return -1;
                                    // Default to one minute.
                                default:
                                    console.debug("invalid index for measurement removal time")
                                    return 60;
                                }
                            }
                        }
                    }
                    ListItem.Standard {
                        id: rpfConversion
                        text: "Automatically convert RPF files to ASCII"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.convertRpfToAscii
                            onClicked: GuiSettings.convertRpfToAscii = !GuiSettings.convertRpfToAscii
                        }
                    }
                    ListItem.Standard {
                        id: rpfAddToMap
                        text: "Automatically add RPF files to map layer"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.addRpfToMap
                            onClicked: GuiSettings.addRpfToMap = !GuiSettings.addRpfToMap
                        }
                    }
                }
            }

            Item { height: dp(32); width: page.cardWidth }
            ListItem.Subheader { text: "Power Spectrum" }
            Card {
                width: page.cardWidth
                height: spectrumColumn.height
                Column {
                    id: spectrumColumn
                    width: parent.width
                    height: childrenRect.height
                    ListItem.Standard {
                        height: dp(70)
                        text: "Log spectrum data to file"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.isSpectrumLogged
                            onClicked: GuiSettings.isSpectrumLogged = !GuiSettings.isSpectrumLogged
                        }
                    }
                    ListItem.Standard {
                        height: dp(70)
                        text: "Dwell time"
                        secondaryItem: Slider {
                            id: spectrumDwellTimeSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: true
                            stepSize: 5
                            minimumValue: 10
                            maximumValue: 60
                            knobLabel: value + " ms"
                            alwaysShowValueLabel: true
                            value: GuiSettings.spectrumDwellTime / 1000000
                            onValueChanged: GuiSettings.spectrumDwellTime = spectrumDwellTimeSlider.value * 1000000
                        }
                    }
                    ListItem.Standard {
                        height: dp(70)
                        text: "Bin size"
                        secondaryItem: Slider {
                            id: spectrumBinSizeSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: true
                            stepSize: 1
                            minimumValue: 1
                            maximumValue: 20
                            knobLabel: value + " kHz"
                            alwaysShowValueLabel: true
                            value: GuiSettings.spectrumBinSize / 1000
                            onValueChanged: GuiSettings.spectrumBinSize = spectrumBinSizeSlider.value * 1000
                        }
                    }
                }
            }

            Item { height: dp(32); width: page.cardWidth }
            ListItem.Subheader { text: "Carrier Wave" }
            Card {
                width: page.cardWidth
                height: cwColumn.height
                Column {
                    id: cwColumn
                    width: parent.width
                    height: childrenRect.height
                    ListItem.Standard {
                        height: dp(70)
                        text: "Dwell time"
                        secondaryItem: Slider {
                            id: cwDwellTimeSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: true
                            stepSize: 5
                            minimumValue: 10
                            maximumValue: 60
                            knobLabel: value + " ms"
                            alwaysShowValueLabel: true
                            value: GuiSettings.cwDwellTime / 1000000
                            onValueChanged: GuiSettings.cwDwellTime = cwDwellTimeSlider.value * 1000000
                        }
                    }
                    ListItem.Standard {
                        height: dp(70)
                        text: "Bandwidth"
                        secondaryItem: Slider {
                            id: cwBinSizeSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: true
                            stepSize: .5
                            minimumValue: .5
                            maximumValue: 5
                            knobLabel: value + " kHz"
                            alwaysShowValueLabel: true
                            value: GuiSettings.cwBinSize / 1000
                            onValueChanged: GuiSettings.cwBinSize = cwBinSizeSlider.value * 1000
                        }
                    }
                }
            }

            Item { height: dp(32); width: page.cardWidth }
            ListItem.Subheader { text: "IQ Data" }
            Card {
                width: page.cardWidth
                height: iqColumn.height
                Column {
                    id: iqColumn
                    width: parent.width
                    height: childrenRect.height
                    ListItem.Standard {
                        height: dp(70)
                        text: "Dwell time"
                        secondaryItem: Slider {
                            id: iqDwellTimeSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: true
                            stepSize: 5
                            minimumValue: 10
                            maximumValue: 100
                            knobLabel: value + " ms"
                            alwaysShowValueLabel: true
                            value: GuiSettings.iqDwellTime / 1000000
                            onValueChanged: GuiSettings.iqDwellTime = iqDwellTimeSlider.value * 1000000
                        }
                    }
                    ListItem.Subtitled {
                        height: dp(70)
                        text: "Bandwidth"
                        subText: "Valid bandwidth must be lower than sampling rate"
                        secondaryItem: Slider {
                            id: iqBandwidthSlider
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.verticalCenterOffset: dp(5)
                            numericValueLabel: true
                            tickmarksEnabled: false
                            stepSize: .5
                            minimumValue: 1.5
                            maximumValue: 28
                            knobLabel: value + " mHz"
                            alwaysShowValueLabel: true
                            value: GuiSettings.iqBandwidth / 1000000
                            onValueChanged: {
                                 if(iqBandwidthSlider.value * 1000000 > GuiSettings.iqSamplingRate) {
                                     value = GuiSettings.iqSamplingRate / 1000000;
                                 }
                                 else
                                      GuiSettings.iqBandwidth = iqBandwidthSlider.value * 1000000
                            }
                        }
                    }
                    ListItem.Subtitled {
                        height: dp(70)
                        text: "SamplingRate"
                        subText: "Valid sampling rates range from 0.8 mHz to 40 mHz"
                        secondaryItem: RowLayout {
                            anchors.centerIn: parent
                            TextField {
                                id: iqSamplingRateText
                                Layout.alignment: Qt.AlignCenter
                                validator: DoubleValidator{
                                    bottom: .8
                                    top: 40
                                    decimals: 6
                                    notation: DoubleValidator.StandardNotation
                                }
                                Component.onCompleted: text = GuiSettings.iqSamplingRate / 1000000
                                onTextChanged: if(acceptableInput) GuiSettings.iqSamplingRate = text.valueOf(text) * 1000000
                            }
                            Label {
                                Layout.alignment: Qt.AlignCenter
                                style: "body1"
                                text: "mHz"
                            }
                        }
                    }
                }
            }

            Item { height: dp(32); width: page.cardWidth }
            ListItem.Subheader { text: "Logging" }
            Card {
                width: page.cardWidth
                height: loggingColumn.height
                Column {
                    id: loggingColumn
                    width: parent.width
                    height: childrenRect.height
                    ListItem.Subtitled {
                        text: "Application verbosity"
                        subText: "Verbosity level for main application log"
                        secondaryItem: MenuField {
                            id: logLevelAppVerbosityMenu
                            anchors.centerIn: parent
                            implicitWidth: dp(16*8)
                            implicitHeight: parent.height
                            model: [ "Verbose", "Debug", "Info", "Warning", "Error", "Critical"]
                            floatingLabel: false
                            maxVisibleItems: 6
                            function setVerbosity(index) {
                                GuiSettings.logLevelAppVerbosity = index;
                            }
                            Component.onCompleted: {
                                logLevelAppVerbosityMenu.selectedIndex = GuiSettings.logLevelAppVerbosity;
                                logLevelAppVerbosityMenu.itemSelected.connect(setVerbosity);
                            }
                        }
                    }
                    ListItem.Subtitled {
                        text: "GPS"
                        subText: "Log GPS communication and parsing"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.loggingGps
                            onClicked: GuiSettings.loggingGps = !GuiSettings.loggingGps
                        }
                    }
                    ListItem.Subtitled {
                        text: "Collection"
                        subText: "Log processing flow and packet parameters"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.loggingCollection
                            onClicked: GuiSettings.loggingCollection = !GuiSettings.loggingCollection
                        }
                    }
                    ListItem.Subtitled {
                        text: "Packets"
                        subText: "Log raw packets"
                        secondaryItem: Switch {
                            anchors.centerIn: parent
                            checked: GuiSettings.loggingPackets
                            onClicked: GuiSettings.loggingPackets = !GuiSettings.loggingPackets
                        }
                    }
                    ListItem.Subtitled {
                        text: "Hardware verbosity"
                        subText: "Verbosity level for hardware log"
                        secondaryItem: MenuField {
                            id: hardwareVerbosityMenu
                            anchors.centerIn: parent
                            implicitWidth: dp(16*8)
                            implicitHeight: parent.height
                            model: [ "Verbose", "Debug", "Info", "Warning", "Error", "Critical"]
                            floatingLabel: false
                            maxVisibleItems: 6
                            function setVerbosity(index) {
                                GuiSettings.logLevelHardwareVerbosity = index;
                            }
                            Component.onCompleted: {
                                hardwareVerbosityMenu.selectedIndex = GuiSettings.logLevelHardwareVerbosity;
                                hardwareVerbosityMenu.itemSelected.connect(setVerbosity)
                            }
                        }
                    }
                    Rectangle { height: dp(8); width: parent.width }
                    RowLayout {
                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }
                        Rectangle { Layout.fillWidth: true }
                        Button {
                            text: "Apply log settings"
                            textColor: Theme.primaryColor
                            onClicked: page.apply()
                        }
                    }
                }
            }
            Item {
                Layout.fillHeight: true
            }
        }
    }

    Scrollbar {
        flickableItem: flickable
    }

    FileDialog {
        id: rpfConversionDialog
        visible: false
        title: "Choose RPF Files For Conversion"
        nameFilters: [ "rf phreaker files (*.rpf)" ]
        modality: Qt.WindowModal
        folder: shortcuts.documents
        selectedNameFilter: "rf phreaker files (*.rpf)"
        sidebarVisible: true
        selectExisting: true
        selectMultiple: true
        onAccepted: {
            console.log("RPF files to convert: " + fileUrls);
            for(var i = 0; i < fileUrls.length; ++i)
                Api.convertRfp(fileUrls[i]);
        }
        onRejected: { console.log("Canceled RPF conversion dialog.") }
    }
}
