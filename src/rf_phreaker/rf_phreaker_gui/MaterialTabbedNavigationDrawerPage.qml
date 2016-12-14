/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.6
import Material 0.3
import Material.Extras 0.1
import Material.ListItems 0.1 as ListItem
import QtQuick.Controls 1.4 as Controls
import QtQuick.Layouts 1.1
import RfPhreaker 1.0

TabbedPage {
    id: navPage

    property var snackbar: __snackbar
    property alias logHeight: __logViewContainer.height
    property alias logVisible: __logViewContainer.visible

    backAction: navDrawer.action
    title: page.title
    actions: page.actions
    actionBar.backgroundColor: page.actionBar.backgroundColor
    actionBar.decorationColor: page.actionBar.decorationColor
    tabs: page.tabs ? page.tabs : ""

    onSelectedTabIndexChanged: {
        tabs.currentIndex = navPage.selectedTabIndex;
    }
    property var navDrawer

    property var page

    function navigate(page) {
        stackView.push({ item: page, replace: true })
        navPage.page = stackView.currentItem;
        navDrawer.close()
    }

    onNavDrawerChanged: navDrawer.parent = navPage

    Controls.SplitView {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: __snackbar.top
        orientation: Qt.Vertical

        Controls.StackView {
            id: stackView
            width: parent.width
            Layout.fillHeight: true
        }

        Rectangle {
            id: __logViewContainer
            anchors.bottom: parent.bottom
            anchors.bottomMargin: (__logViewContainer.percentOpen - 1) * height
            width: parent.width
            Layout.maximumHeight: navPage.height / 2
            height: Math.max(dp(200), navPage.height / 2)
            visible: false

            property real percentOpen: visible ? 1 : 0
            Behavior on percentOpen {
                NumberAnimation {
                    duration: 200
                    easing {
                        type: Easing.OutCubic
                    }
                }
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.topMargin: dp(16)
                anchors.leftMargin: dp(16)
                anchors.rightMargin: dp(16)
                spacing: dp(16)
                Row {
                    spacing: dp(16)
                    IconButton {
                        anchors.verticalCenter: parent.verticalCenter
                        iconName: "content/clear"
                        size: dp(32)
                        onClicked: logVisible = false
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: dp(24)
                        font.family: "Roboto"
                        font.weight: Font.DemiBold
                        color: Theme.light.subTextColor
                        text: "Application Log"
                    }
                }
                ListView {
                    id: __logView
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: Api.log
                    clip: true
                    delegate: Row {
                        height: label.height
                        Label {
                            id: label
                            width: dp(130)
                            text: modelData.time
                        }
                        Label {
                            text: modelData.detailsMsg
                        }
                    }
                    Scrollbar {
                        flickableItem: __logView
                    }
                }
            }
        }
    }
    Snackbar {
        id: __snackbar
        anchors.bottom: parent.bottom
        property var messages: new Array(0)
        Component.onCompleted: {
            Api.messagesChanged.connect(__snackbar.store)
        }
        signal store()
        onStore: {
            messages.push(Api.newestMessage);
            showMessageAndShift();
        }
        onOpenedChanged: {
            if(messages.length) {
                showMessageAndShift();
            }
        }
        function showMessageAndShift() {
            if(!opened) {
                __snackbar.open(messages.shift().details);
            }
        }
    }

}
