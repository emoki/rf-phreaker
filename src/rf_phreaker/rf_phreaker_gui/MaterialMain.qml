import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import Material 0.3
import Material.ListItems 0.1 as ListItem
import RfPhreaker 1.0

ApplicationWindow {
    id: rpWindow

    property alias stateMachine: dsmOperation
    property alias openScannerDialog: __openScannerDialog
    property alias snackbar: navPage.snackbar
    property alias startCollectionDialog: __startCollectionDialog
    property alias messageDialog: __messageDialog
    property alias logVisible: navPage.logVisible

    title: ""

    visible: true

    function showLog() {
        if(navPage.logHeight === 0)
            navPage.logHeight = dp(400);
        logVisible = true;
    }

    function hideLog() {
        logVisible = false;
    }

    theme {
        primaryColor: GuiSettings.themePrimaryColor
        accentColor: GuiSettings.themeAccentColor
        tabHighlightColor: GuiSettings.themeTabHighlightColor
    }

    property var pages: [
            "Dashboard", "Measurements", "Navigation", "Settings"
    ]

    property string selectedComponent: pages[0]

    //initialPage: MaterialMeasurementsPage {id: tmp; anchors.fill: parent}

    initialPage: MaterialTabbedNavigationDrawerPage {
        id: navPage

        Component.onCompleted: navPage.navigate(Qt.resolvedUrl("Material%Page.qml").arg(rpWindow.selectedComponent.replace(" ", "")))

        navDrawer: NavigationDrawer {
            id: navDrawer

            Flickable {
                anchors.fill: parent

                contentHeight: Math.max(content.implicitHeight, height)

                Column {
                    id: content
                    anchors.fill: parent

                    Repeater {
                        model: pages
                        delegate: ListItem.Standard {
                            text: modelData
                            selected: modelData == rpWindow.selectedComponent
                            onClicked: {
                                rpWindow.selectedComponent = modelData
                                navPage.navigate(Qt.resolvedUrl("Material%Page.qml").arg(rpWindow.selectedComponent.replace(" ", "")));
                                navDrawer.close()
                            }
                        }
                    }
                }
            }
        }
    }

    onClosing: {
        console.debug("Closing main app!");
        dsmOperation.stop();
        Api.cleanUpApi();
    }

    Settings {
        id: settings
        category: "rpWindow"
        property var x
        property var y
        property var width
        property var height
        property var xHistory: rpWindow.visibility === Window.Windowed ? rpWindow.x : x
        property var yHistory: rpWindow.visibility === Window.Windowed ? rpWindow.y : y
        property var widthHistory: rpWindow.visibility === Window.Windowed ? rpWindow.width : width
        property var heightHistory: rpWindow.visibility === Window.Windowed ? rpWindow.height : height
        property alias logHeight: navPage.logHeight
        property alias logVisible: rpWindow.logVisible
        property var visibility
        Component.onDestruction: {
            x = xHistory;
            y = yHistory;
            width = widthHistory;
            height = heightHistory;
        }
    }

    Component.onCompleted: {
        closing.connect(beforeClosing);
        console.debug("settings", settings.x, settings.y, settings.width, settings.height)
        if(settings.visibility === Window.Maximized) {
            rpWindow.showMaximized();
        }
        else {
            rpWindow.x = settings.x;
            rpWindow.y = settings.y
            rpWindow.width = settings.width
            rpWindow.height = settings.height
        }
    }

    function beforeClosing() {
        console.debug("closing window", rpWindow.visibility)
        settings.visibility = rpWindow.visibility
    }

    onVisibilityChanged: {
        if(visibility === Window.Windowed) {
            rpWindow.x = settings.x;
            rpWindow.y = settings.y
            rpWindow.width = settings.width
            rpWindow.height = settings.height
        }
    }

    MaterialStateMachine {
        id: dsmOperation
    }

    //MaterialOpenScannerDialog {
    SelectScannerWindow {
        id: __openScannerDialog
    }

    Dialog {
        id: __messageDialog
        width: dp(400)
        title: Api.newestError.mainDescription
        text: Api.newestError.details
        negativeButton.visible: false
    }

    FileSaveDialog{
        id: __startCollectionDialog
        visible: false
        title: "Please choose the collection filename"
        nameFilters: [ "rf phreaker files (*.rpf)", "kml files (*.kml)", "All files (*)" ]
//        modality: Qt.WindowModal
//        folder: shortcuts.documents
//        selectedNameFilter: "rf phreaker files (*.rfp)"
//        sidebarVisible: true
        onAccepted: {
            Api.collectionFilename = fileUrl;
            console.log("Collection filename is " + fileUrl);
            rpWindow.stateMachine.startRecording();
        }
        onRejected: { console.log("Cancelled save collection filename.") }
    }
}
