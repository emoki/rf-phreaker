/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.4
import Material 0.3
import QtQuick.Controls 1.4 as Controls
import RfPhreaker 1.0

TabbedPage {
    id: navPage

    property var snackbar: __snackbar

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

    Controls.StackView {
        id: stackView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: __snackbar.top
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
