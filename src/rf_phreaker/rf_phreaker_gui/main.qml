import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: "Scanner"
            MenuItem {
                text: "RF Bands"
            }
            MenuItem {
                text: "Valid Licenses"
            }
            MenuItem {
                text: "Input License"
            }
        }
        Menu {
            title: "Plot"
            MenuItem {
                text: "Spectrum"
            }
            MenuItem {
                text: "WCDMA"
            }
            MenuItem {
                text: "LTE"
            }
            MenuItem {
                text: "Raw IQ Polar"
            }
            MenuItem {
                text: "Raw IQ Magnitude"
            }
        }
        Menu {
            title: "Drill Down"
            MenuItem {
                text: "WCDMA"
            }
            MenuItem {
                text: "LTE"
            }
        }
    }
    toolBar: ToolBar {
        id: toolbar
        RowLayout {
            width: parent.width
            Layout.alignment: Qt.LeftToRight

            ToolButton {
                text: "what?"
            }
            ToolButton {
                text: "huh?"
            }
        }
    }

    SplitView {
        anchors.fill: parent
        ChannelList {
            width:400
        }
        TableView {
            Label {
                text: "how"
            }
        }
    }

    statusBar: StatusBar {
        width: parent.width
    }
}
