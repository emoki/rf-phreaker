import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1
import Material 0.3
import RfPhreaker 1.0

Card {
    id: card
    property int width0: dp(200)
    property int height0: dp(56)
    property int width1: dp(350)
    property int height1: dp(215)
    property int width2: dp(350*2+16)
    property int height2: dp(215*2+16)
    property int width3: dp(350*3+16*2)
    property int height3: dp(215*3+16*2)

    state: "w1h1"

    states: [
        State {
            name: "w0h0"
            PropertyChanges { target: card; width: width0; height: height0; }
        },
        State {
            name: "w1h1"
            PropertyChanges { target: card; width: width1; height: height1; }
        },
        State {
            name: "w2h2"
            PropertyChanges { target: card; width: width2; height: height2; }
        },
        State {
            name: "w3h3"
            PropertyChanges { target: card; width: width3; height: height3; }
        },
        State {
            name: "w1h0"
            PropertyChanges { target: card; width: width0; height: height0; }
        },
        State {
            name: "w1h1"
            PropertyChanges { target: card; width: width1; height: height1; }
        },
        State {
            name: "w1h2"
            PropertyChanges { target: card; width: width1; height: height2; }
        },
        State {
            name: "w1h3"
            PropertyChanges { target: card; width: width1; height: height3; }
        },
        State {
            name: "w2h0"
            PropertyChanges { target: card; width: width2; height: height0; }
        },
        State {
            name: "w2h1"
            PropertyChanges { target: card; width: width2; height: height1; }
        },
        State {
            name: "w2h2"
            PropertyChanges { target: card; width: width2; height: height2; }
        },
        State {
            name: "w2h3"
            PropertyChanges { target: card; width: width2; height: height3; }
        }
    ]

    Behavior on width {
        NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
    }

    Behavior on height {
        NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
    }

//    ColumnLayout {
//        RowLayout {
//            Item {
//                id: headerItem
//                visible: children.length > 1
//            }
//        }
//        Item {
//            id: contentItem
//            visible: children.length > 1
//        }

//        RowLayout {
//            Layout.alignment: Qt.AlignRight
//            spacing: dp(8)

//            anchors {
//                right: parent.right
//                left: parent.left
//                rightMargin: dp(8)
//                leftMargin: dp(8)
//            }

//            Item {
//                id: footerItem
//                visible: children.length > 1
//            }

//        }
//    }
}
