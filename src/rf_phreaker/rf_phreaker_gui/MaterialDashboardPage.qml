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

    title: "RF Phreaker Dashboard"

    actionBar.maxActionCount: 5

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

    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: parent.width;
        contentHeight: layout.childrenRect.height + dp(16)

        Flow {
            id: layout

            anchors {
                fill: parent
                topMargin: dp(16)
                bottomMargin: dp(16)
                leftMargin: dp(16)
                rightMargin: dp(16)
            }

            spacing: dp(16)

            Column {
                spacing: dp(16)
                width: childrenRect.width
                height: childrenRect.height

                MaterialCard {
                    id: rpCard
                    state: rpExpBut.expanded ? "w1h2" : "w1h1"

                    Item {
                        anchors.fill: parent

                        ProgressCircle {
                            id: determinateProgress
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: rpStatus.height + dp(16)
                            width: dp(64)
                            height: dp(64)
                            indeterminate: false
                            minimumValue: 0
                            maximumValue: 100
                            visible: Api.connectionStatus === ApiTypes.CONNECTING

                            SequentialAnimation on value {
                                running: Api.connectionStatus === ApiTypes.CONNECTING
                                NumberAnimation {
                                    duration: 18000
                                    from: determinateProgress.minimumValue
                                    to: determinateProgress.maximumValue - 1
                                }
                            }

                            Label {
                                anchors.centerIn: parent
                                text: Math.round(determinateProgress.value) + "%"
                            }
                        }
                    }

                    ColumnLayout {
                        anchors {
                            fill: parent
                            topMargin: dp(24)
                            bottomMargin: dp(8)
                        }

                        ColumnLayout {
                            anchors {
                                top: parent.top
                                right: parent.right
                                left: parent.left
                                rightMargin: dp(16)
                                leftMargin: dp(16)
                            }
                            Label {
                                id: rpStatus
                                style: "headline"
                                states: [
                                    State {
                                        when: Api.connectionStatus === ApiTypes.DISCONNECTED
                                        PropertyChanges {
                                            target: rpStatus
                                            text: Api.deviceStatus === ApiTypes.ERROR ? "RF Phreaker Disconnected (Error)" : "RF Phreaker Disconnected"
                                        }
                                    },
                                    State {
                                        when: Api.connectionStatus === ApiTypes.CONNECTING
                                        PropertyChanges {
                                            target: rpStatus
                                            text: "RF Phreaker Connecting"
                                        }
                                    },
                                    State {
                                        when: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus == ApiTypes.ERROR
                                        PropertyChanges {
                                            target: rpStatus
                                            text: "RF Phreaker Idle (Error)"
                                        }
                                    },
                                    State {
                                        when: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus == ApiTypes.IDLE
                                        PropertyChanges {
                                            target: rpStatus
                                            text: "RF Phreaker Idle"
                                        }
                                    },
                                    State {
                                        when: Api.connectionStatus === ApiTypes.CONNECTED && Api.deviceStatus == ApiTypes.RECORDING
                                        PropertyChanges {
                                            target: rpStatus
                                            text: "RF Phreaker Recording"
                                        }
                                    }
                                ]
                            }

                            Label {
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectedDevice.serial
                            }
                            Label {
                                id: freqCorrectionDate
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectionStatus === ApiTypes.CONNECTED
                                      ? "Frequency Correction performed on " + Api.connectedDevice.freqCorrectionDateStr + "."
                                      : ""
                            }
                            Label {
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectionStatus === ApiTypes.CONNECTED
                                      ? "RF Calibration Date performed on " + Api.connectedDevice.rfCalibrationDateStr + "."
                                      : ""
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: dp(8)
                            }
                        }
                        RowLayout {
                            Layout.alignment: Qt.AlignRight
                            spacing: dp(8)

                            anchors {
                                right: parent.right
                                left: parent.left
                                rightMargin: dp(8)
                                leftMargin: dp(8)
                            }
                            Item {
                                width: childrenRect.width
                                height: childrenRect.height
                                Button {
                                    text: "Disconnect"
                                    textColor: Theme.primaryColor
                                    visible: Api.connectionStatus === ApiTypes.CONNECTED
                                    onClicked: rpWindow.stateMachine.disconnectScanner();

                                }
                                Button {
                                    text: "Connect"
                                    textColor: Theme.primaryColor
                                    visible: Api.connectionStatus !== ApiTypes.CONNECTED && Api.connectionStatus !== ApiTypes.CONNECTING
                                    onClicked: rpWindow.stateMachine.connectScanner();
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                            MaterialExpansionButton {
                                id: rpExpBut
                            }
                        }
                    }
                }

                MaterialCard {
                    state: gpsExpBut.expanded ? "w1h2" : "w1h1"
                    ColumnLayout {
                        anchors {
                            fill: parent
                            topMargin: dp(24)
                            bottomMargin: dp(8)
                        }

                        ColumnLayout {
                            anchors {
                                top: parent.top
                                right: parent.right
                                left: parent.left
                                rightMargin: dp(16)
                                leftMargin: dp(16)
                            }
                            Label {
                                style: "headline"
                                text: Api.connectionStatus === ApiTypes.CONNECTED
                                      ? (Api.gps.gpsLock ? "Position Locked" : "Position Not Locked")
                                      : "Position Not Available"
                            }
                            Label {
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectionStatus === ApiTypes.CONNECTED && Api.gps.init
                                      ? Api.gps.utcDateTimeStr : ""
                            }
                            //                    Label {
                            //                        style: "body1"
                            //                        color: Theme.light.subTextColor
                            //                        text: Number(Api.gps.latitude).toPrecision(6)
                            //                    }
                            //                    Label {
                            //                        style: "body1"
                            //                        color: Theme.light.subTextColor
                            //                        text: Number(Api.gps.longitude).toPrecision(6)
                            //                    }
                            Label {
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectionStatus === ApiTypes.CONNECTED && Api.gps.init
                                      ? Api.gps.trackingSatellites + " Tracking Satellites"
                                      : ""
                            }
                            Label {
                                style: "body1"
                                color: Theme.light.subTextColor
                                text: Api.connectionStatus === ApiTypes.CONNECTED && Api.gps.init
                                      ? Api.gps.visibleSatellites + " Visible Satellites"
                                      : ""
                            }
                            Item {
                                Layout.fillWidth: true
                                Layout.preferredHeight: dp(8)
                            }
                        }
                        RowLayout {
                            Layout.alignment: Qt.AlignRight
                            spacing: dp(8)

                            anchors {
                                right: parent.right
                                left: parent.left
                                rightMargin: dp(8)
                                leftMargin: dp(8)
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                            MaterialExpansionButton {
                                id: gpsExpBut
                            }
                        }
                    }
                }
            }

            MaterialCard {
//                property int minHeight: scanListTitle.height + Api.scanList.rowCount * dp(32) + collectionInfoSuggestionText.height + dp(18)
//                property int h2
                state: scanListExpBut.expanded ? "w2h3" : "w1h2"
//                state: scanListExpBut.expanded ? "w2h3" : "w2h1"

//                height2: minHeight

//                Component.onCompleted: { h2 = hieght; }

                ColumnLayout {
                    id: scanListLayout
                    anchors {
                        fill: parent
                        topMargin: dp(24)
                        bottomMargin: dp(8)
                    }

                    Label {
                        id: scanListTitle
                        Layout.fillWidth: true
                        Layout.rightMargin: dp(16)
                        Layout.leftMargin: dp(16)
                        visible: true//scanListExpBut.expanded
                        style: "headline"
                        text: "Collection List"
                    }
                    Rectangle {
                        visible: !scanListExpBut.expanded
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        GridView {
                            id: minScanList
                            anchors.fill: parent
                            model: Api.scanList

                            cellWidth: width/* / 2*/
                            cellHeight: dp(32)

                            delegate: ListItem.Standard {
                                height: dp(32)

                                width: minScanList.cellWidth
                                anchors.right: undefined
                                anchors.left: undefined

                                content: Label {
                                    anchors.top: parent.top
                                    anchors.bottom: parent.bottom
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                    style: "body1"

                                    text: {
                                        if(isSweep)
                                            return "Sweeping " + band
                                        else
                                            return "Scanning " + radioType + " " + channels
                                    }
                                }
                                secondaryItem: IconButton {
                                    anchors.top: parent.top
                                    anchors.bottom: parent.bottom
                                    iconName: "content/remove"
                                    color: Theme.light.textColor
                                    onClicked: Api.scanList.remove(index);
                                }
                            }
                        }
                    }

                    Rectangle {
                        visible: scanListExpBut.expanded
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        ListView {
                            anchors.fill: parent
                            model: Api.scanList
                            delegate: ListItem.Subtitled {
                                Layout.fillWidth: false
                                showDivider: true
                                text: {
                                    if(isSweep)
                                        return "Sweeping " + channels
                                    else
                                        return "Scanning " + channels
                                }
                                valueText: freqs
                                subText: band + " - " + info
                                secondaryItem: IconButton {
                                    iconName: "content/remove"
                                    color: Theme.light.textColor
                                    anchors.verticalCenter: parent.verticalCenter
                                    onClicked: Api.scanList.remove(index);
                                }
                            }
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: dp(8)
                    }
                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: dp(8)

                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }

                        SuggestionTextField {
                            id: collectionInfoSuggestionText

                            Layout.fillWidth: true

                            floatingLabel: false

                            placeholderText: "Input band, channel, or frequency here."

                            sSearch: search
                            sView: suggestView

                            function doSelectionAction(item) {
                                console.debug("Updating rpCollectionInfoList with ", selectedItem);
                                Api.scanList.add(selectedItem);
                            }

                            onClose: menu.close()
                            onToggleOpen: {
                                if(suggestView.rowCount === 0 && menu.state === "open")
                                    menu.close();
                                else if(suggestView.rowCount > 0 && menu.state === "closed") {
                                    menu.open(collectionInfoSuggestionText, 0, collectionInfoSuggestionText.height)
                                    suggestView.currentRow = -1;
                                }
                            }
                        }
                        MaterialExpansionButton {
                            id: scanListExpBut
                        }
                    }
                    Item {
                        id: dropTableView
                        Layout.alignment: Qt.AlignVCenter
                        Layout.fillWidth: true
                        property int maxVisibleItems: 4

                        Dropdown {
                            id: menu

                            anchor: Item.TopLeft
                            closeOnResize: false

                            width: dropTableView.width * 2 < layout.width - dp(100)
                                   ? dropTableView.width * 2
                                   : layout.width - dp(100)

                            //If there are more than max items, show an extra half item so
                            // it's clear the user can scroll
                            height: Math.min(dropTableView.maxVisibleItems*48 * Units.dp + 24 * Units.dp, (search.results.length) * 48 * Units.dp + dp(2))

                            SuggestionView {
                                id: suggestView
                                property bool aboveSuggestionTextField: true

                                anchors.fill:parent
                                visible: menu.opacity === 1

                                suggestionModel: search.results
                                sTextField: collectionInfoSuggestionText

                                rowDelegate: MaterialRowDelegate{ control: suggestView }

                                onClose: {
                                    // Update details in case something was added.
                                    //scanDetails.updateStats()
                                    menu.close()
                                }

                                Controls.TableViewColumn {
                                    horizontalAlignment: Text.AlignLeft
                                    title: "Tech"
                                    role: "tech"
                                    width: suggestView.width * .25
                                    delegate: MaterialItemDelegate { isNumber: false; control: suggestView }
                                }
                                Controls.TableViewColumn {
                                    horizontalAlignment: Text.AlignLeft
                                    title: "Band"
                                    role: "band"
                                    width: suggestView.width * .25
                                    delegate: MaterialItemDelegate { isNumber: false; control: suggestView }
                                }
                                Controls.TableViewColumn {
                                    horizontalAlignment: Text.AlignRight
                                    title: "Frequency Range"
                                    role: "freqs"
                                    width: suggestView.width * .25
                                    delegate: MaterialItemDelegate { isNumber: false; control: suggestView }
                                }
                                Controls.TableViewColumn {
                                    horizontalAlignment: Text.AlignRight
                                    title: "Channel Range"
                                    role:  "channels"
                                    width: suggestView.width * .25
                                    delegate: MaterialItemDelegate { isNumber: false; control: suggestView }
                                }
                            }
                        }
                    }
                }

            }

            MaterialCard {
                state: mapExpBut.expanded ? "w4h4" : "w2h2"
                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true
                    hoverEnabled: true
                    onEntered: flickable.interactive = false
                    onExited: flickable.interactive = true
                }

                ColumnLayout {
                    anchors {
                        fill: parent
                        bottomMargin: dp(8)
                    }
                    spacing: dp(8)

                    MaterialMarbleMap {
                        id: dashboardMarbleMap
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        visible: true
                        focus: true

                        MaterialMarbleLocationButton {
                            marbleManager: dashboardMarbleMap.marbleManager
                            anchors {
                                right: dashboardMarbleMap.right
                                bottom: dashboardMarbleMap.bottom
                                margins: dp(32)
                            }
                            isMiniSize: true
                        }
                    }

                    RowLayout {
                        spacing: dp(8)

                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }

                        Button {
                            text: "Manager Layers"
                            textColor: Theme.primaryColor
                            visible: true
                            onClicked: dashboardMarbleMap.layerPopup.open()
                        }
                        Button {
                            text: "Download Current Area"
                            textColor: Theme.primaryColor
                            visible: true
                            onClicked: dashboardMarbleMap.marbleManager.downloadMapRegion()
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        MaterialExpansionButton {
                            id: mapExpBut
                        }
                    }
                }
            }

            MaterialCard {
                state: lteExpBut.expanded ? "w2h3" : "w1h2"
                ColumnLayout {
                    anchors {
                        fill: parent
                        topMargin: dp(24)
                        bottomMargin: dp(8)
                        rightMargin: dp(16)
                        leftMargin: dp(16)
                    }
                    Label {
                        style: "headline"
                        text: "LTE Measurements"
                    }
                    BarChart {
                        id: lteBarChart
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        sourceModel:  FilterProxyMeasurementModel {
                            id: filterLte
                            sourceModel: Api.lteModels.fullScanModel
                            filterRole: FilterProxyMeasurementModel.TimeFilter
                            expirationTimeFilter: GuiSettings.measurementRemovalTime

                        }
                        Timer {
                            interval: 1000
                            running: true
                            repeat: true
                            onTriggered: filterLte.refilter()
                        }

                        slMin: -120
                        slMax: -10
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: dp(8)
                    }
                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: dp(8)

                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        MaterialExpansionButton {
                            id: lteExpBut
                        }
                    }
                }
            }

            MaterialCard {
                state: wcdmaExpBut.expanded ? "w2h3" : "w1h2"
                ColumnLayout {
                    anchors {
                        fill: parent
                        topMargin: dp(24)
                        bottomMargin: dp(8)
                        rightMargin: dp(16)
                        leftMargin: dp(16)
                    }

                    Label {
                        style: "headline"
                        text: "WCDMA Measurements"
                    }
                    BarChart {
                        id: wcdmaBarChart
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        sourceModel: FilterProxyMeasurementModel {
                            id: filterWcdma
                            sourceModel: Api.wcdmaModels.fullScanModel
                            filterRole: FilterProxyMeasurementModel.TimeFilter
                            expirationTimeFilter: GuiSettings.measurementRemovalTime

                        }
                        Timer {
                            interval: 1000
                            running: true
                            repeat: true
                            onTriggered: filterWcdma.refilter()
                        }

                        slMin: -120
                        slMax: -10
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: dp(8)
                    }
                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: dp(8)

                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        MaterialExpansionButton {
                            id: wcdmaExpBut
                        }
                    }
                }
            }

            MaterialCard {
                state: gsmExpBut.expanded ? "w2h3" : "w1h2"
                ColumnLayout {
                    anchors {
                        fill: parent
                        topMargin: dp(24)
                        bottomMargin: dp(8)
                        rightMargin: dp(16)
                        leftMargin: dp(16)
                    }

                    Label {
                        style: "headline"
                        text: "GSM Measurements"
                    }
                    BarChart {
                        id: gsmBarChart
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        sourceModel: FilterProxyMeasurementModel {
                            id: filterGsm
                            sourceModel: Api.gsmModels.fullScanModel
                            filterRole: FilterProxyMeasurementModel.TimeFilter
                            expirationTimeFilter: GuiSettings.measurementRemovalTime

                        }
                        Timer {
                            interval: 1000
                            running: true
                            repeat: true
                            onTriggered: filterGsm.refilter()
                        }

                        slMin: -120
                        slMax: -10
                    }
                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: dp(8)
                    }
                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: dp(8)

                        anchors {
                            right: parent.right
                            left: parent.left
                            rightMargin: dp(8)
                            leftMargin: dp(8)
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        MaterialExpansionButton {
                            id: gsmExpBut
                        }
                    }
                }
            }

            move: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: 200;
                    easing.type: Easing.InOutQuad
                }
            }

            CollectionInfoSearch {
                id: search
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
